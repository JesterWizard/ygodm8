#!/usr/bin/env python3
import argparse
import audioop
import hashlib
import html
import json
import re
import struct
import sys
import wave
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(Path(__file__).resolve().parent))
from dpcm_fast_lookup_table import DPCM_FAST_LOOKUP
ASSETS = ROOT / "src_custom/assets/voices"
VOICE_INVENTORY_MD = ASSETS / "VOICES.md"
GENERATED = ROOT / "src_custom/generated"
HEADER = ROOT / "include/constants/custom_voices_generated.h"
BASEROM = ROOT / "baserom.gba"
VOICE_INPUT_HEADERS = (
    ROOT / "include/ai.h",
    ROOT / "include/overworld.h",
    ROOT / "include/constants/card_ids.h",
)
DUELIST_TABLE_OFF = 0xE00B30

# m4a WaveData.freq pitch constant (NOT literal Hz). Vanilla duel VO uses 21024 Hz (= 0x01488000).
M4A_WAVE_FREQ = 0x01488000
M4A_WAVE_SAMPLE_RATE = 21024
M4A_TONE_GROUP_PTR = 0x08AFB2CC
M4A_TONE_TABLE_ORG = 0xAFB2CC
M4A_SONG_TABLE_ORG = 0xAFBDE4
M4A_SONG_MODE_TABLE_ORG = 0x80D29D0 - 0x08000000
M4A_VOICE_PLAYER = 3
M4A_VOICE_SONG_PLAYER = 0x00030003
M4A_VOICE_SONG_MODE = 3
M4A_TONE_INDEX_MAX = 255
M4A_VANILLA_DUEL_VOICE_TONE = 47
M4A_SONG_SCAN_MAX = 800
# Prefer high unused tone indices; never patch 48-83 (shared by many BGM/SFX part tracks).
M4A_VOICE_TONE_PREFER_MIN = 128
CUSTOM_VOICE_PART_TONE_INDEX = 0
CUSTOM_VOICE_PART_SIZE = 18
CUSTOM_VOICE_WAVE_HEADER_SIZE = 16
M4A_WAVE_TYPE_PCM = 0
M4A_WAVE_TYPE_DPCM = 1
DPCM_BLOCK_SAMPLES = 64
DPCM_BLOCK_BYTES = 33  # initial + 32 packed bytes (first packed: low nibble only)
DPCM_LOOKUP = (0, 1, 4, 9, 16, 25, 36, 49, -64, -49, -36, -25, -16, -9, -4, -1)

# Tail ROM: voice PCM @ VOICE_PCM_ROM_ORG, then append (code/assets). See ldscript.ld + validate_lynjump.
VOICE_PCM_ROM_ORG = 0x08FE3400
MAX_ROM_LIMIT = 0x0A000000
# Reserve headroom for appended code/assets (~768 KiB; current append ~660 KiB).
APPEND_ROM_RESERVE = 0x000C0000

# m4a D0–FF note length table (gClockTable / gScaleTable slice used by ply_note).
M4A_NOTE_LENGTH_TABLE = (
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 28, 30, 32, 36, 40, 42, 44, 48,
    52, 54, 56, 60, 64, 66, 68, 72, 76, 78, 80, 84, 88, 90, 92, 96,
)

# Vanilla duel VO @ tempo 0x14 (BB). Verified against baserom tone/part pairs @ 21024 Hz.
# Playback stops at min(WaveData.size, note gate capacity); WaveData.size is exact PCM length.
M4A_VOICE_NOTE_KEY = 0x3C
M4A_VOICE_NOTE_VEL = 0x7F
M4A_VOICE_PART_TEMPO = 0x14
M4A_VOICE_PART_VOLUME = 0x74

# Longest vanilla duel voice note (tone 47 @ 53938 samples). Covers all clips <= this size.
M4A_VOICE_MAX_VANILLA_NOTE = bytes([0xED, 0x3C, 0x7F, 0x9E])
M4A_VOICE_MAX_VANILLA_SAMPLES = 53938

# Empirical gate-capacity model fit from baserom calibration (samples ≈ a*ticks + b*idx + c).
M4A_NOTE_CAPACITY_A = 1379.9035041566324
M4A_NOTE_CAPACITY_B = -1518.908555193228
M4A_NOTE_CAPACITY_C = -178249.88882458786
M4A_NOTE_CAPACITY_MARGIN = 512

# Baserom (sample_count, note bytes) for encoder regression tests.
M4A_VOICE_NOTE_CALIBRATION = (
    (14124, bytes([0xDA, 0x3C, 0x7F, 0x8B])),
    (19369, bytes([0xE0, 0x3C, 0x7F, 0x91])),
    (20993, bytes([0xE0, 0x3C, 0x7F, 0x91])),
    (22763, bytes([0xE1, 0x3C, 0x7F, 0x92])),
    (40581, bytes([0xE9, 0x3C, 0x7F, 0x9A, 0x81])),
    (44609, bytes([0xEB, 0x3C, 0x7F, 0x9C])),
    (50871, bytes([0xEC, 0x3C, 0x7F, 0x9D])),
    (53938, bytes([0xED, 0x3C, 0x7F, 0x9E])),
)
# Normalize all clips to this 16-bit peak before 8-bit conversion (32767 ≈ full s8 range).
PCM8_TARGET_PEAK = 32767
# Leave headroom before DPCM encode so quantization + HQ mix do not clip harshly.
PCM8_DPCM_TARGET_PEAK = 24576
# Edge-trim samples with |value| <= threshold after 8-bit conversion (near silence).
PCM8_SILENCE_TRIM_THRESHOLD = 8
PCM8_SILENCE_TRIM_DEFAULT = True

TRIGGER_TURN_START = 0
TRIGGER_ATTACK_CARD = 1
TRIGGER_OPPONENT_LP_BELOW = 2

TRIGGER_BY_NAME = {
    "turn_start": TRIGGER_TURN_START,
    "attack_card": TRIGGER_ATTACK_CARD,
    "opponent_lp_below": TRIGGER_OPPONENT_LP_BELOW,
}


def load_ai_duelist_ids():
    text = (ROOT / "include/ai.h").read_text()
    match = re.search(r"\benum\s+AiDuelistId\s*\{(.*?)\};", text, re.DOTALL)
    if not match:
        raise SystemExit("enum AiDuelistId not found in include/ai.h")
    constants = {}
    value = 0
    for raw_item in match.group(1).split(","):
        item = raw_item.strip()
        if not item:
            continue
        item = re.sub(r"//.*", "", item).strip()
        if not item:
            continue
        name, _, explicit = item.partition("=")
        name = name.strip()
        if explicit:
            value = int(explicit.strip().split()[0], 0)
        constants[name] = value
        if not explicit:
            value += 1
    return constants


def load_card_ids():
    text = (ROOT / "include/constants/card_ids.h").read_text()
    constants = {}
    for line in text.splitlines():
        match = re.match(r"#define\s+(\w+)\s+(0x[0-9A-Fa-f]+|\d+)", line)
        if match:
            constants[match.group(1)] = int(match.group(2), 0)
    return constants


def load_opponent_ids():
    text = (ROOT / "include/overworld.h").read_text()
    match = re.search(r"\benum\s+DuelistId\s*\{(.*?)\};", text, re.DOTALL)
    if not match:
        raise SystemExit("enum DuelistId not found in include/overworld.h")

    constants = {}
    value = 0
    for raw_item in match.group(1).split(","):
        item = raw_item.strip()
        if not item:
            continue
        item = re.sub(r"//.*", "", item).strip()
        if not item:
            continue
        name, _, explicit = item.partition("=")
        name = name.strip()
        if explicit:
            value = int(explicit.strip().split()[0], 0)
        constants[name] = value
        if not explicit:
            value += 1
    return constants


def load_duelist_voice_id(opponent_index):
    if not BASEROM.is_file():
        raise SystemExit(f"missing {BASEROM} (needed to resolve DUELIST_* voice ids)")

    rom = BASEROM.read_bytes()
    ptr = struct.unpack_from("<I", rom, DUELIST_TABLE_OFF + opponent_index * 4)[0]
    if ptr < 0x08000000:
        raise SystemExit(f"opponent index {opponent_index}: null duelist pointer")

    return struct.unpack_from("<H", rom, ptr - 0x08000000)[0]


CUSTOM_VOICE_OPPONENT_ANY = 0xFFFF


def resolve_duelist_target(raw_duelist, ai_ids, opponent_ids):
    if isinstance(raw_duelist, int):
        return {
            "voice_id": raw_duelist,
            "opponent_id": CUSTOM_VOICE_OPPONENT_ANY,
            "ref": str(raw_duelist),
        }

    if raw_duelist in ai_ids:
        return {
            "voice_id": ai_ids[raw_duelist],
            "opponent_id": CUSTOM_VOICE_OPPONENT_ANY,
            "ref": raw_duelist,
        }

    if raw_duelist in opponent_ids:
        opponent_index = opponent_ids[raw_duelist]
        return {
            "voice_id": load_duelist_voice_id(opponent_index),
            "opponent_id": opponent_index,
            "ref": raw_duelist,
        }

    raise SystemExit(f"unknown duelist {raw_duelist!r} (expected AI_DUELIST_* or DUELIST_*)")


def resolve_duelist_targets(raw_duelist, ai_ids, opponent_ids):
    if isinstance(raw_duelist, list):
        if not raw_duelist:
            raise SystemExit("duelist list cannot be empty")
        return [resolve_duelist_target(item, ai_ids, opponent_ids) for item in raw_duelist]
    return [resolve_duelist_target(raw_duelist, ai_ids, opponent_ids)]


def read_wav_mono_pcm8(path, target_rate, gain_db=0.0):
    with wave.open(str(path), "rb") as wf:
        channels = wf.getnchannels()
        sample_width = wf.getsampwidth()
        frame_rate = wf.getframerate()
        frames = wf.readframes(wf.getnframes())

    if sample_width != 2:
        raise SystemExit(f"{path}: expected 16-bit WAV, got {sample_width * 8}-bit")

    if channels == 2:
        frames = audioop.tomono(frames, sample_width, 0.5, 0.5)
        channels = 1
    elif channels != 1:
        raise SystemExit(f"{path}: expected mono or stereo WAV, got {channels} channels")

    if frame_rate != target_rate:
        frames, _ = audioop.ratecv(frames, sample_width, channels, frame_rate, target_rate, None)

    if gain_db:
        frames = audioop.mul(frames, sample_width, 10 ** (gain_db / 20))

    peak = audioop.max(frames, sample_width)
    if peak > 0:
        frames = audioop.mul(frames, sample_width, PCM8_DPCM_TARGET_PEAK / peak)

    pcm8 = audioop.lin2lin(frames, sample_width, 1)
    return pcm8, target_rate


def pcm8_to_signed_samples(pcm8):
    return [pcm8_sample_value(byte) for byte in pcm8]


def signed_samples_to_pcm8(samples):
    out = bytearray()
    for sample in samples:
        if sample < -128:
            sample = -128
        elif sample > 127:
            sample = 127
        out.append(sample & 0xFF)
    return bytes(out)


def apply_pcm8_edge_fade(pcm8, fade_samples=24):
    """Short fade in/out to avoid edge clicks after silence trim."""
    if fade_samples <= 0 or len(pcm8) < fade_samples * 2:
        return pcm8

    samples = pcm8_to_signed_samples(pcm8)
    for i in range(fade_samples):
        scale = (i + 1) / fade_samples
        samples[i] = int(samples[i] * scale)
        tail = len(samples) - fade_samples + i
        samples[tail] = int(samples[tail] * (fade_samples - i) / fade_samples)
    return signed_samples_to_pcm8(samples)


def pcm8_sample_value(byte):
    return byte if byte < 128 else byte - 256


def trim_silence_edges_pcm8(pcm8, threshold=PCM8_SILENCE_TRIM_THRESHOLD):
    """Remove leading/trailing near-silence from signed 8-bit mono PCM."""
    if threshold < 0 or not pcm8:
        return pcm8

    n = len(pcm8)
    lead = 0
    for byte in pcm8:
        if abs(pcm8_sample_value(byte)) > threshold:
            break
        lead += 1
    if lead >= n:
        return pcm8

    trail = 0
    for byte in reversed(pcm8):
        if abs(pcm8_sample_value(byte)) > threshold:
            break
        trail += 1
    end = n - trail
    if end <= lead:
        return pcm8
    return pcm8[lead:end]


def resolve_trim_settings(manifest, entry):
    enabled = entry.get("trim_silence", manifest.get("trim_silence", PCM8_SILENCE_TRIM_DEFAULT))
    threshold = entry.get(
        "trim_silence_threshold",
        manifest.get("trim_silence_threshold", PCM8_SILENCE_TRIM_THRESHOLD),
    )
    return bool(enabled), int(threshold)


def apply_silence_trim(pcm8, manifest, entry):
    enabled, threshold = resolve_trim_settings(manifest, entry)
    if not enabled:
        return pcm8
    return trim_silence_edges_pcm8(pcm8, threshold)


def symbol_for_clip(clip_id):
    safe = re.sub(r"[^A-Za-z0-9_]", "_", clip_id)
    if safe[0].isdigit():
        safe = f"v_{safe}"
    return safe


def c_escape_string(text: str) -> str:
    out = []
    for ch in text:
        if ch == "\\":
            out.append("\\\\")
        elif ch == '"':
            out.append('\\"')
        elif ch == "\n":
            out.append("\\n")
        elif ord(ch) >= 32 and ord(ch) < 127:
            out.append(ch)
        else:
            out.append(f"\\x{ord(ch):02x}")
    return "".join(out)


def encode_duel_turn_text(text: str) -> str:
    """Duel textbox format: $0..$5 language chunks, $6 end marker, #1 wait for A/B/R."""
    body = text.replace("\\n", "\n").replace("\n", "#0")
    segments = "".join(f"${lang}{body}" for lang in range(6))
    return segments + "$6#1"


def turn_text_symbol_for(sym: str) -> str:
    return f"CustomVoice_{sym}_TurnText"


def song_const_for_clip(clip_id):
    return f"SFX_VOICE_{symbol_for_clip(clip_id).upper()}"


def parse_part_track_tone_indices(part_ptr, rom):
    """Return m4a tone indices referenced by a song part track."""
    if not part_ptr:
        return set()

    off = part_ptr - 0x08000000
    if off < 0 or off >= len(rom):
        return set()

    data = rom[off : off + 2048]
    tones = set()
    i = 0
    while i < len(data):
        byte = data[i]
        if byte == 0xBD and i + 1 < len(data):
            tones.add(data[i + 1])
            i += 2
            continue
        if byte == 0xF2 and i + 2 < len(data):
            tones.add(data[i + 2])
            i += 3
            continue
        if byte == 0x81 and i + 1 < len(data):
            tones.add(data[i + 1])
            i += 2
            continue
        if byte == 0xB1:
            break
        i += 1
    return tones


def scan_baserom_used_tone_indices(rom_path=BASEROM, max_songs=M4A_SONG_SCAN_MAX):
    """Tone indices referenced by baserom song part tracks (0..max_songs-1)."""
    if not rom_path.is_file():
        raise SystemExit(f"missing {rom_path} (needed to allocate unused m4a tone slots)")

    rom = rom_path.read_bytes()
    used = set()
    for song in range(max_songs):
        off = M4A_SONG_TABLE_ORG + song * 8
        if off + 8 > len(rom):
            break
        header_ptr, _player = struct.unpack_from("<II", rom, off)
        if header_ptr < 0x08000000 or header_ptr >= 0x09000000:
            continue
        hoff = header_ptr - 0x08000000
        if hoff + 12 > len(rom):
            continue
        part_ptr = struct.unpack_from("<I", rom, hoff + 8)[0]
        used.update(parse_part_track_tone_indices(part_ptr, rom))
    return used


def allocate_voice_tone_indices(num_clips, used_tones):
    """Pick unused m4a tone slots so voice DPCM patches do not hijack BGM instruments."""
    forbidden = set(used_tones)
    forbidden.add(M4A_VANILLA_DUEL_VOICE_TONE)

    unused_high = sorted(
        i
        for i in range(M4A_TONE_INDEX_MAX + 1)
        if i not in forbidden and i >= M4A_VOICE_TONE_PREFER_MIN
    )
    unused_low = sorted(
        i for i in range(M4A_TONE_INDEX_MAX + 1) if i not in forbidden and i < M4A_VOICE_TONE_PREFER_MIN
    )
    chosen = (unused_high + unused_low)[:num_clips]
    if len(chosen) < num_clips:
        raise SystemExit(
            f"need {num_clips} free m4a tone slots for custom voices, "
            f"only {len(chosen)} unused in baserom (scan 0-{M4A_TONE_INDEX_MAX})"
        )
    return chosen


def resolve_card_targets(raw_card_id, card_ids):
    if isinstance(raw_card_id, list):
        if not raw_card_id:
            raise SystemExit("card_id list cannot be empty")
        return [
            {
                "card_id": card_ids[name],
                "ref": name,
            }
            for name in raw_card_id
        ]
    return [
        {
            "card_id": card_ids.get(raw_card_id, 0xFFFF),
            "ref": raw_card_id,
        }
    ]


def validate_clip(entry, ai_ids, opponent_ids, card_ids, sample_rate, manifest=None):
    clip_id = entry["clip_id"]
    trigger = entry["trigger"]
    wav_rel = entry["wav"]
    wav_path = ASSETS / wav_rel

    resolve_duelist_targets(entry["duelist"], ai_ids, opponent_ids)
    if trigger not in TRIGGER_BY_NAME:
        raise SystemExit(f"{clip_id}: unknown trigger {trigger!r}")
    if not wav_path.is_file():
        raise SystemExit(f"{clip_id}: missing WAV {wav_path}")

    gain_db = entry.get("gain_db", 0.0)
    pcm8, rate = read_wav_mono_pcm8(wav_path, sample_rate, gain_db)
    pcm8 = apply_silence_trim(pcm8, manifest or {}, entry)
    pcm8 = apply_pcm8_edge_fade(pcm8)
    if rate != sample_rate:
        raise SystemExit(f"{clip_id}: resample failed")

    if trigger == "attack_card" and "card_id" not in entry:
        raise SystemExit(f"{clip_id}: attack_card requires card_id")
    if trigger == "opponent_lp_below" and "lp_threshold" not in entry:
        raise SystemExit(f"{clip_id}: opponent_lp_below requires lp_threshold")
    if trigger == "attack_card":
        for target in resolve_card_targets(entry["card_id"], card_ids):
            if target["ref"] not in card_ids:
                raise SystemExit(f"{clip_id}: unknown card_id {target['ref']!r}")
    if "turn_text" in entry and trigger not in ("turn_start", "opponent_lp_below"):
        raise SystemExit(f"{clip_id}: turn_text is only valid for turn_start or opponent_lp_below")


def m4a_note_ticks(cmd, gate, extra=None):
    idx = cmd - 0xD0
    if idx < 0 or idx >= len(M4A_NOTE_LENGTH_TABLE):
        raise ValueError(f"invalid m4a note cmd 0x{cmd:02X}")
    ticks = M4A_NOTE_LENGTH_TABLE[idx] + gate
    if extra is not None:
        if extra < 0x81 or extra > 0xB0:
            raise ValueError(f"invalid m4a wait/extra byte 0x{extra:02X}")
        ticks += M4A_NOTE_LENGTH_TABLE[extra - 0x81]
    return ticks, idx


def estimate_note_sample_capacity(cmd, gate, extra=None):
    ticks, idx = m4a_note_ticks(cmd, gate, extra)
    return (
        M4A_NOTE_CAPACITY_A * ticks
        + M4A_NOTE_CAPACITY_B * idx
        + M4A_NOTE_CAPACITY_C
    )


def build_voice_part_note(cmd, gate, extra=None):
    note = bytes([cmd, M4A_VOICE_NOTE_KEY, M4A_VOICE_NOTE_VEL, gate])
    if extra is not None:
        note += bytes([extra])
    if len(note) not in (4, 5):
        raise ValueError(f"part note must be 4 or 5 bytes, got {len(note)}")
    return note


def encode_part_track_note(sample_count):
    """Pick m4a note bytes whose gate capacity covers sample_count (no PCM padding)."""
    if sample_count <= 0:
        raise SystemExit(f"voice clip has no PCM samples ({sample_count})")

    if sample_count <= M4A_VOICE_MAX_VANILLA_SAMPLES:
        return M4A_VOICE_MAX_VANILLA_NOTE

    target = sample_count + M4A_NOTE_CAPACITY_MARGIN
    best = None

    for cmd in range(0xD0, 0x100):
        for gate in range(256):
            cap = estimate_note_sample_capacity(cmd, gate)
            if cap >= target:
                waste = cap - sample_count
                cand = (waste, cmd, gate, None)
                if best is None or cand < best:
                    best = cand
            for extra in range(0x81, 0xB1):
                cap = estimate_note_sample_capacity(cmd, gate, extra)
                if cap >= target:
                    waste = cap - sample_count
                    cand = (waste, cmd, gate, extra)
                    if best is None or cand < best:
                        best = cand

    if best is None:
        raise SystemExit(
            f"no m4a part-track note covers {sample_count} samples "
            f"(max vanilla gate is {M4A_VOICE_MAX_VANILLA_SAMPLES})"
        )

    _waste, cmd, gate, extra = best
    return build_voice_part_note(cmd, gate, extra)


def prepare_pcm_and_note(pcm8):
    sample_count = len(pcm8)
    note = encode_part_track_note(sample_count)
    return pcm8, note, sample_count


def clamp_s8(value):
    if value < -128:
        return -128
    if value > 127:
        return 127
    return value


def dpcm_fast_nibbles(target, prev_level):
    idx = target - prev_level + 255
    if idx < 0 or idx >= len(DPCM_FAST_LOOKUP):
        return range(16)
    return DPCM_FAST_LOOKUP[idx]


def encode_dpcm_block(block):
    if len(block) != DPCM_BLOCK_SAMPLES:
        raise ValueError(f"DPCM block must be {DPCM_BLOCK_SAMPLES} samples")

    lookup = DPCM_LOOKUP
    clamp = clamp_s8
    fast_nibbles = dpcm_fast_nibbles

    dp = {block[0]: 0.0}
    parent = []

    for idx in range(1, DPCM_BLOCK_SAMPLES):
        target = block[idx]
        next_dp = {}
        par = {}
        for level, cost in dp.items():
            for nibble in fast_nibbles(target, level):
                new_level = clamp(level + lookup[nibble])
                error = cost + (target - new_level) ** 2
                if new_level not in next_dp or error < next_dp[new_level]:
                    next_dp[new_level] = error
                    par[new_level] = (level, nibble)
        dp = next_dp
        parent.append(par)

    level = min(dp, key=dp.get)
    nibbles = [0] * (DPCM_BLOCK_SAMPLES - 1)
    for step in range(len(parent) - 1, -1, -1):
        level, nibble = parent[step][level]
        nibbles[step] = nibble

    out = [block[0] & 0xFF, nibbles[0] & 0xF]
    for byte_num in range(2, DPCM_BLOCK_BYTES):
        nibble_idx = (byte_num - 2) * 2 + 1
        packed = ((nibbles[nibble_idx] & 0xF) << 4) | (nibbles[nibble_idx + 1] & 0xF)
        out.append(packed)

    if len(out) != DPCM_BLOCK_BYTES:
        raise ValueError(
            f"DPCM block payload is {len(out)} bytes, expected {DPCM_BLOCK_BYTES}"
        )
    return bytes(out)


def encode_dpcm_pcm8(pcm8):
    samples = list(struct.unpack(f"{len(pcm8)}b", pcm8))
    out = bytearray()
    pos = 0
    while pos < len(samples):
        block = samples[pos : pos + DPCM_BLOCK_SAMPLES]
        if len(block) < DPCM_BLOCK_SAMPLES:
            pad = block[-1] if block else 0
            block = block + [pad] * (DPCM_BLOCK_SAMPLES - len(block))
        out.extend(encode_dpcm_block(block))
        pos += DPCM_BLOCK_SAMPLES
    return bytes(out)


def decode_dpcm_block(block_data):
    if len(block_data) != DPCM_BLOCK_BYTES:
        raise ValueError(
            f"DPCM block payload is {len(block_data)} bytes, expected {DPCM_BLOCK_BYTES}"
        )

    out = []
    level = struct.unpack("b", bytes([block_data[0]]))[0]
    out.append(level)

    packed = block_data[1]
    nibble = packed & 0xF
    level = clamp_s8(level + DPCM_LOOKUP[nibble])
    out.append(level)

    for byte_idx in range(2, DPCM_BLOCK_BYTES):
        packed = block_data[byte_idx]
        for shift in (4, 0):
            nibble = (packed >> shift) & 0xF
            level = clamp_s8(level + DPCM_LOOKUP[nibble])
            out.append(level)

    if len(out) != DPCM_BLOCK_SAMPLES:
        raise ValueError(
            f"DPCM block decoded {len(out)} samples, expected {DPCM_BLOCK_SAMPLES}"
        )
    return out


def decode_dpcm_pcm8(dpcm_payload, sample_count):
    out = bytearray()
    pos = 0
    while len(out) < sample_count:
        block = dpcm_payload[pos : pos + DPCM_BLOCK_BYTES]
        if len(block) != DPCM_BLOCK_BYTES:
            raise ValueError(
                f"DPCM payload truncated at byte {pos} "
                f"(need {DPCM_BLOCK_BYTES}, got {len(block)})"
            )
        pos += DPCM_BLOCK_BYTES
        for sample in decode_dpcm_block(block):
            if len(out) >= sample_count:
                break
            out.append(sample & 0xFF)
    return bytes(out[:sample_count])


def dpcm_payload_size(sample_count):
    blocks = (sample_count + DPCM_BLOCK_SAMPLES - 1) // DPCM_BLOCK_SAMPLES
    return blocks * DPCM_BLOCK_BYTES


def dpcm_wave_bytes_for(sample_count):
    wave_bytes = CUSTOM_VOICE_WAVE_HEADER_SIZE + dpcm_payload_size(sample_count)
    if wave_bytes & 1:
        wave_bytes += 1
    return wave_bytes


def validate_dpcm_payload(pcm8, payload):
    decoded = decode_dpcm_pcm8(payload, len(pcm8))
    if len(decoded) != len(pcm8):
        raise SystemExit(
            f"DPCM round-trip length mismatch ({len(pcm8)} vs {len(decoded)} samples)"
        )
    if len(payload) % DPCM_BLOCK_BYTES != 0:
        raise SystemExit(
            f"DPCM payload size {len(payload)} is not a multiple of {DPCM_BLOCK_BYTES}"
        )


def encode_dpcm_pcm8_validated(pcm8):
    payload = encode_dpcm_pcm8(pcm8)
    validate_dpcm_payload(pcm8, payload)
    return payload


def validate_dpcm_codec(pcm8, payload=None):
    """Round-trip check. When payload is omitted, encode once and return it."""
    if payload is None:
        return encode_dpcm_pcm8_validated(pcm8)
    validate_dpcm_payload(pcm8, payload)
    return payload


def part_track_tail(note):
    if len(note) == 5:
        return bytes([0xB1, 0x00, 0x00, 0x01, 0x00])
    return bytes([0xB1, 0x00, 0x00, 0x00, 0x01, 0x00])


def build_part_track(tone_index, note):
    part = bytearray(
        [
            0xBC,
            0x00,
            0xBB,
            M4A_VOICE_PART_TEMPO,
            0xBD,
            tone_index,
            0xBE,
            M4A_VOICE_PART_VOLUME,
        ]
    )
    part.extend(note)
    part.extend(part_track_tail(note))
    if len(part) != CUSTOM_VOICE_PART_SIZE:
        raise SystemExit(
            f"tone {tone_index}: part track is {len(part)} bytes, expected {CUSTOM_VOICE_PART_SIZE}"
        )
    return bytes(part)


def wave_bytes_for(sample_count):
    wave_bytes = CUSTOM_VOICE_WAVE_HEADER_SIZE + sample_count
    if wave_bytes & 1:
        wave_bytes += 1
    return wave_bytes


def render_voice_rom_s(songs_meta, dpcm_blobs):
    lines = [
        "@ Custom voice DPCM WaveData + m4a part tracks + SongHeaders in main ROM (0x08xxxxxx).",
        f"@ DPCM is wav2agb mono @ {M4A_WAVE_SAMPLE_RATE} Hz; WaveData.freq uses 0x{M4A_WAVE_FREQ:08X}.",
        ".section .voice_pcm_rom",
        ".align 4",
        "",
    ]

    for meta, dpcm in zip(songs_meta, dpcm_blobs):
        sym = meta["symbol"]
        part = meta["part_track"]
        part_bytes = ", ".join(f"0x{b:02X}" for b in part)

        lines.append(f".global CustomVoice_{sym}_Wave")
        lines.append(f"CustomVoice_{sym}_Wave:")
        lines.append(f"    .hword {M4A_WAVE_TYPE_DPCM}, 0")
        lines.append(f"    .word 0x{M4A_WAVE_FREQ:08X}")
        lines.append("    .word 0")
        lines.append(f"    .word {meta['sample_count']}")
        byte_lines = [f"0x{b:02X}" for b in dpcm]
        for i in range(0, len(byte_lines), 16):
            chunk = byte_lines[i : i + 16]
            lines.append(f"    .byte {', '.join(chunk)}")
        lines.append(".align 4")
        lines.append("")
        lines.append(f".global CustomVoice_{sym}_Part")
        lines.append(f"CustomVoice_{sym}_Part:")
        lines.append(f"    .byte {part_bytes}")
        lines.append(".align 4")
        lines.append("")
        lines.append(f".global CustomVoice_{sym}_SongHeader")
        lines.append(f"CustomVoice_{sym}_SongHeader:")
        lines.append("    .byte 1, 0, 110, 0  @ trackCount, blockCount, priority, reverb")
        lines.append(f"    .word 0x{M4A_TONE_GROUP_PTR:08X}  @ tone group")
        lines.append(f"    .word CustomVoice_{sym}_Part")
        lines.append(".align 4")
        lines.append("")

    return "\n".join(lines) + "\n"


def render_assets_s(songs_meta, dpcm_blobs):
    return render_voice_rom_s(songs_meta, dpcm_blobs)


def render_header(manifest, songs_meta, clips_meta):
    lines = [
        "#ifndef GUARD_CUSTOM_VOICES_GENERATED_H",
        "#define GUARD_CUSTOM_VOICES_GENERATED_H",
        "",
        f"#define CUSTOM_VOICE_SONG_COUNT {len(songs_meta)}",
        f"#define CUSTOM_VOICE_MATCH_COUNT {len(clips_meta)}",
        f"#define CUSTOM_VOICE_OPPONENT_ANY 0xFFFF",
        f"#define CUSTOM_VOICE_MPLAY_PLAYER {M4A_VOICE_PLAYER}",
        f"#define CUSTOM_VOICE_SONG_ID_MIN {manifest['song_id_base']}",
        f"#define CUSTOM_VOICE_PART_SIZE {CUSTOM_VOICE_PART_SIZE}",
    ]
    if songs_meta:
        lines.append(
            f"#define CUSTOM_VOICE_SONG_ID_MAX {manifest['song_id_base'] + len(songs_meta) - 1}"
        )
    else:
        lines.append(f"#define CUSTOM_VOICE_SONG_ID_MAX {manifest['song_id_base']}")
    lines.append("")
    for meta in songs_meta:
        lines.append(f"#define {meta['song_const']} {meta['song_id']}")
    lines.append("")
    lines.append("enum CustomVoiceTriggerType {")
    lines.append("  CUSTOM_VOICE_TRIGGER_TURN_START = 0,")
    lines.append("  CUSTOM_VOICE_TRIGGER_ATTACK_CARD = 1,")
    lines.append("  CUSTOM_VOICE_TRIGGER_OPPONENT_LP_BELOW = 2,")
    lines.append("};")
    lines.append("")
    lines.append("struct CustomVoiceClipMeta {")
    lines.append("  u16 songId;")
    lines.append("  u16 duelistId;")
    lines.append("  u16 opponentId;")
    lines.append("  u16 cardId;")
    lines.append("  u16 lpThreshold;")
    lines.append("  u8 triggerType;")
    lines.append("  u8 priority;")
    lines.append("  u8 replaceVanilla;")
    lines.append("  u8 songIndex;")
    lines.append("  const u8 *turnText;")
    lines.append("};")
    lines.append("")
    lines.append("void PlayCustomVoiceClip(u8 songIndex);")
    lines.append("")
    lines.append("#endif // GUARD_CUSTOM_VOICES_GENERATED_H")
    lines.append("")
    return "\n".join(lines)


def render_triggers_inc(clips_meta):
    lines = [
        "static const struct CustomVoiceClipMeta sCustomVoiceClips[] APPEND_RODATA = {"
    ]
    for meta in clips_meta:
        lines.append(
            "  {"
            f"{meta['song_const']}, "
            f"{meta['duelist_id']}, "
            f"{meta['opponent_id']}, "
            f"{meta['card_id']}, "
            f"{meta['lp_threshold']}, "
            f"{meta['trigger_type']}, "
            f"{meta['priority']}, "
            f"{meta['replace_vanilla']}, "
            f"{meta['song_index']}, "
            f"{meta['turn_text_ref']}"
            "},"
        )
    lines.append("};")
    lines.append("")
    return "\n".join(lines)


def render_turn_text_inc(songs_meta):
    lines = []
    for meta in songs_meta:
        if "turn_text" not in meta:
            continue
        encoded = encode_duel_turn_text(meta["turn_text"])
        sym = meta["symbol"]
        lines.append(
            f"static const u8 {turn_text_symbol_for(sym)}[] APPEND_RODATA = "
            f'"{c_escape_string(encoded)}";'
        )
    if lines:
        lines.append("")
    return "\n".join(lines)


def render_rom_patches_json(songs_meta):
    tone_patches = []
    song_patches = []
    mode_patches = []
    for meta in songs_meta:
        sym = meta["symbol"]
        tone_patches.append(
            {
                "org": M4A_TONE_TABLE_ORG + meta["tone_index"] * 12,
                "wave_symbol": f"CustomVoice_{sym}_Wave",
            }
        )
        song_patches.append(
            {
                "org": M4A_SONG_TABLE_ORG + meta["song_id"] * 8,
                "header_symbol": f"CustomVoice_{sym}_SongHeader",
                "player": M4A_VOICE_SONG_PLAYER,
            }
        )
        mode_patches.append(
            {
                "org": M4A_SONG_MODE_TABLE_ORG + meta["song_id"],
                "mode": M4A_VOICE_SONG_MODE,
            }
        )
    return (
        json.dumps(
            {
                "tone_patches": tone_patches,
                "song_patches": song_patches,
                "mode_patches": mode_patches,
            },
            indent=2,
        )
        + "\n"
    )


def render_wave_loader_inc(songs_meta):
    lines = []
    for meta in songs_meta:
        sym = meta["symbol"]
        lines.append(f"extern u8 CustomVoice_{sym}_Wave[];")
        lines.append(f"extern u8 CustomVoice_{sym}_Part[];")
    if songs_meta:
        lines.append("")
    lines.extend(
        [
            "struct CustomVoiceRomClip {",
            "  const struct WaveData *dpcmWave;",
            "  const u8 *partTrack;",
            "};",
            "",
            "static const struct CustomVoiceRomClip sCustomVoiceRomClips[] APPEND_RODATA = {",
        ]
    )
    for meta in songs_meta:
        sym = meta["symbol"]
        lines.append(
            f"  {{ (const struct WaveData *)&CustomVoice_{sym}_Wave, CustomVoice_{sym}_Part }},"
        )
    lines.append("};")
    lines.append("")
    return "\n".join(lines)


def render_song_headers_inc(songs_meta):
    lines = []
    for meta in songs_meta:
        sym = meta["symbol"]
        lines.append(f"extern struct SongHeader CustomVoice_{sym}_SongHeader;")
    lines.append("")
    lines.append("static const struct SongHeader * const sCustomVoiceSongHeaders[] APPEND_RODATA = {")
    for meta in songs_meta:
        sym = meta["symbol"]
        lines.append(f"    &CustomVoice_{sym}_SongHeader,")
    lines.append("};")
    lines.append("")
    return "\n".join(lines)


def format_byte_size(num_bytes):
    if num_bytes < 1024:
        return f"{num_bytes} B"
    return f"{num_bytes:,} B ({num_bytes / 1024:.1f} KB)"


def format_colored_size_delta(source_bytes, rom_bytes):
    if source_bytes <= 0:
        return "—"
    delta = (rom_bytes - source_bytes) / source_bytes * 100
    sign = "+" if delta > 0 else ""
    text = f"{sign}{delta:.1f}%"
    if abs(delta) < 0.05:
        return text
    if delta < 0:
        color = "#3fb950"
    else:
        color = "#f85149"
    return f'<span style="color: {color}">{html.escape(text)}</span>'


def render_voice_inventory_md(manifest, songs_meta):
    registered_wavs = {meta["wav_rel"] for meta in songs_meta}
    orphan_wavs = sorted(
        path.relative_to(ASSETS).as_posix()
        for path in ASSETS.rglob("*.wav")
        if path.relative_to(ASSETS).as_posix() not in registered_wavs
    )

    lines = [
        "# Custom Voice Asset Inventory",
        "",
        "Auto-generated by [`tools/generate_voices.py`](../../tools/generate_voices.py) when you run `make`.",
        "",
        "Sizes:",
        "",
        "- **Source WAV** — on-disk `.wav` file size (includes RIFF headers; typically 16-bit PCM).",
        "- **In-ROM** — m4a `WaveData` DPCM blob in main ROM: 16-byte header + wav2agb DPCM payload (+ 1-byte pad if odd).",
        "- **Overall Change** — `(in-ROM − source) / source`; negative means the ROM blob is smaller.",
        "- **Total** row — sum of all registered clips (source vs in-ROM).",
        "- Playback decompresses DPCM to EWRAM PCM at runtime (~50% ROM savings vs raw 8-bit PCM).",
        "- Build trims leading/trailing near-silence (|sample| ≤ 8) before DPCM encode unless disabled in the manifest.",
        "",
        "## Registered clips",
        "",
        "<table>",
        "  <thead>",
        "    <tr>",
        "      <th>Title</th>",
        "      <th>WAV</th>",
        "      <th>Trigger</th>",
        "      <th>Source WAV</th>",
        "      <th>In-ROM</th>",
        "      <th>Overall Change</th>",
        "    </tr>",
        "  </thead>",
        "  <tbody>",
    ]

    if songs_meta:
        total_source_bytes = 0
        total_rom_bytes = 0
        for meta in songs_meta:
            wav_path = ASSETS / meta["wav_rel"]
            source_bytes = wav_path.stat().st_size if wav_path.is_file() else 0
            rom_bytes = meta["wave_bytes"]
            total_source_bytes += source_bytes
            total_rom_bytes += rom_bytes
            title = html.escape(meta["title"])
            wav_rel = html.escape(meta["wav_rel"])
            trigger = html.escape(meta["trigger"])
            lines.append(
                "    <tr>"
                f"<td>{title}</td>"
                f"<td><code>{wav_rel}</code></td>"
                f"<td><code>{trigger}</code></td>"
                f"<td>{format_byte_size(source_bytes)}</td>"
                f"<td>{format_byte_size(rom_bytes)}</td>"
                f"<td>{format_colored_size_delta(source_bytes, rom_bytes)}</td>"
                "</tr>"
            )
        lines.append(
            "    <tr>"
            '<td colspan="3"><strong>Total</strong></td>'
            f"<td><strong>{format_byte_size(total_source_bytes)}</strong></td>"
            f"<td><strong>{format_byte_size(total_rom_bytes)}</strong></td>"
            f"<td><strong>{format_colored_size_delta(total_source_bytes, total_rom_bytes)}</strong></td>"
            "</tr>"
        )
    else:
        lines.append('    <tr><td colspan="6"><em>none</em></td></tr>')

    lines.extend(
        [
            "  </tbody>",
            "</table>",
        ]
    )

    lines.extend(
        [
            "",
            f"_Sample rate: {manifest.get('sample_rate', M4A_WAVE_SAMPLE_RATE)} Hz · "
            f"{len(songs_meta)} clip(s) in [`tools/voice_manifest.json`](../../tools/voice_manifest.json)._",
        ]
    )

    if orphan_wavs:
        lines.extend(
            [
                "",
                "## Unregistered WAVs",
                "",
                "These files exist under `src_custom/assets/voices/` but are not listed in the manifest:",
                "",
            ]
        )
        for wav_rel in orphan_wavs:
            wav_path = ASSETS / wav_rel
            lines.append(f"- `{wav_rel}` ({format_byte_size(wav_path.stat().st_size)})")

    lines.append("")
    return "\n".join(lines)


def render_debug_inc(songs_meta):
    lines = []
    for meta in songs_meta:
        title = meta["title"].replace('"', '\\"')
        lines.append(f'DEBUG_MENU_VOICE_ENTRY({meta["song_const"]}, "{title}")')
    return "\n".join(lines) + ("\n" if lines else "")


def iter_voice_wav_paths():
    if not ASSETS.is_dir():
        return []
    return sorted(ASSETS.rglob("*.wav"))


def file_stat_digest(path: Path, hasher) -> None:
    hasher.update(path.as_posix().encode())
    stat = path.stat()
    hasher.update(str(stat.st_mtime_ns).encode())
    hasher.update(str(stat.st_size).encode())


def compute_voice_inputs_digest(manifest_path: Path, generator_path: Path) -> str:
    hasher = hashlib.sha256()
    file_stat_digest(manifest_path.resolve(), hasher)
    file_stat_digest(generator_path.resolve(), hasher)
    lookup_table = generator_path.parent / "dpcm_fast_lookup_table.py"
    if lookup_table.is_file():
        file_stat_digest(lookup_table.resolve(), hasher)
    for header in VOICE_INPUT_HEADERS:
        if header.is_file():
            file_stat_digest(header, hasher)
    for wav_path in iter_voice_wav_paths():
        file_stat_digest(wav_path.relative_to(ROOT), hasher)
        hasher.update(wav_path.read_bytes())
    return hasher.hexdigest()


def stamp_is_current(stamp_path: Path, digest: str) -> bool:
    if not stamp_path.is_file():
        return False
    return stamp_path.read_text().strip() == digest


DEFAULT_DPCM_CACHE_DIR = ROOT / ".cache" / "voice_dpcm"
DPCM_CACHE_DIR = DEFAULT_DPCM_CACHE_DIR


def dpcm_encoder_version(generator_path: Path) -> str:
    hasher = hashlib.sha256()
    hasher.update(generator_path.read_bytes())
    lookup_table = generator_path.parent / "dpcm_fast_lookup_table.py"
    if lookup_table.is_file():
        hasher.update(lookup_table.read_bytes())
    hasher.update(str(DPCM_BLOCK_SAMPLES).encode())
    hasher.update(str(PCM8_TARGET_PEAK).encode())
    hasher.update(str(PCM8_DPCM_TARGET_PEAK).encode())
    hasher.update(str(M4A_WAVE_SAMPLE_RATE).encode())
    hasher.update(str(PCM8_SILENCE_TRIM_DEFAULT).encode())
    hasher.update(str(PCM8_SILENCE_TRIM_THRESHOLD).encode())
    return hasher.hexdigest()


def clip_dpcm_cache_key(
    wav_path: Path,
    gain_db: float,
    sample_rate: int,
    encoder_version: str,
    trim_silence: bool,
    trim_threshold: int,
) -> str:
    hasher = hashlib.sha256()
    hasher.update(encoder_version.encode())
    hasher.update(str(sample_rate).encode())
    hasher.update(repr(gain_db).encode())
    hasher.update(str(trim_silence).encode())
    hasher.update(str(trim_threshold).encode())
    hasher.update(wav_path.read_bytes())
    return hasher.hexdigest()


def clip_dpcm_cache_paths(clip_id: str) -> tuple[Path, Path]:
    safe_id = re.sub(r"[^A-Za-z0-9_.-]", "_", clip_id)
    base = DPCM_CACHE_DIR / safe_id
    return base.with_suffix(".dpcm"), base.with_suffix(".dpcm.key")


def load_cached_dpcm(clip_id: str, cache_key: str) -> bytes | None:
    dpcm_path, key_path = clip_dpcm_cache_paths(clip_id)
    if not dpcm_path.is_file() or not key_path.is_file():
        return None
    if key_path.read_text().strip() != cache_key:
        return None
    return dpcm_path.read_bytes()


def save_cached_dpcm(clip_id: str, cache_key: str, payload: bytes) -> None:
    dpcm_path, key_path = clip_dpcm_cache_paths(clip_id)
    dpcm_path.parent.mkdir(parents=True, exist_ok=True)
    dpcm_path.write_bytes(payload)
    key_path.write_text(cache_key + "\n")


def get_or_encode_dpcm_payload(
    clip_id: str,
    pcm8: bytes,
    wav_path: Path,
    gain_db: float,
    sample_rate: int,
    encoder_version: str,
    trim_silence: bool,
    trim_threshold: int,
) -> bytes:
    cache_key = clip_dpcm_cache_key(
        wav_path,
        gain_db,
        sample_rate,
        encoder_version,
        trim_silence,
        trim_threshold,
    )
    cached = load_cached_dpcm(clip_id, cache_key)
    if cached is not None:
        validate_dpcm_payload(pcm8, cached)
        print(f"CACHED {clip_id} ({len(cached)} bytes)")
        return cached

    payload = encode_dpcm_pcm8_validated(pcm8)
    save_cached_dpcm(clip_id, cache_key, payload)
    print(f"ENCODE {clip_id} ({len(payload)} bytes)")
    return payload


def write_outputs(outputs: dict[Path, str]) -> bool:
    changed = False
    for path, content in outputs.items():
        path.parent.mkdir(parents=True, exist_ok=True)
        if not path.exists() or path.read_text() != content:
            path.write_text(content)
            print(f"WROTE {path.relative_to(ROOT)}")
            changed = True
        else:
            print(f"OK    {path.relative_to(ROOT)}")
    return changed


def validate_note_encoder():
    for sample_count, _note in M4A_VOICE_NOTE_CALIBRATION:
        encoded = encode_part_track_note(sample_count)
        extra = encoded[4] if len(encoded) > 4 else None
        cap = estimate_note_sample_capacity(encoded[0], encoded[3], extra)
        if cap + M4A_NOTE_CAPACITY_MARGIN < sample_count:
            raise SystemExit(
                f"note encoder under-estimates baserom calibration "
                f"({sample_count} samples, cap≈{cap:.0f})"
            )


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("manifest", type=Path)
    parser.add_argument("--out-dir", type=Path, default=GENERATED)
    parser.add_argument(
        "--stamp",
        type=Path,
        default=None,
        help="Write input digest when outputs are rebuilt; skip work if digest matches.",
    )
    parser.add_argument(
        "--dpcm-cache-dir",
        type=Path,
        default=DEFAULT_DPCM_CACHE_DIR,
        help="Per-clip DPCM encode cache (survives make clean-build).",
    )
    args = parser.parse_args()

    cache_dir = args.dpcm_cache_dir.resolve()
    cache_dir.mkdir(parents=True, exist_ok=True)
    globals()["DPCM_CACHE_DIR"] = cache_dir
    legacy_cache = ROOT / "build" / "voice_dpcm_cache"
    if legacy_cache.is_dir() and not any(cache_dir.iterdir()):
        import shutil

        shutil.copytree(legacy_cache, cache_dir, dirs_exist_ok=True)

    generator_path = Path(__file__).resolve()
    digest = compute_voice_inputs_digest(args.manifest, generator_path)
    if args.stamp and stamp_is_current(args.stamp, digest):
        return

    validate_note_encoder()

    manifest = json.loads(args.manifest.read_text())
    ai_ids = load_ai_duelist_ids()
    opponent_ids = load_opponent_ids()
    card_ids = load_card_ids()

    sample_rate = manifest.get("sample_rate", M4A_WAVE_SAMPLE_RATE)
    song_id_base = manifest["song_id_base"]
    clips = manifest.get("clips", [])

    if not clips:
        raise SystemExit("voice_manifest.json: clips array is empty")

    used_tones = scan_baserom_used_tone_indices()
    voice_tone_indices = allocate_voice_tone_indices(len(clips), used_tones)

    songs_meta = []
    clips_meta = []
    dpcm_blobs = []
    encoder_version = dpcm_encoder_version(generator_path)

    for entry in clips:
        trigger = entry["trigger"]
        validate_clip(entry, ai_ids, opponent_ids, card_ids, sample_rate, manifest)

        wav_path = ASSETS / entry["wav"]
        gain_db = entry.get("gain_db", 0.0)
        trim_silence, trim_threshold = resolve_trim_settings(manifest, entry)
        pcm8, _ = read_wav_mono_pcm8(wav_path, sample_rate, gain_db)
        pcm8 = apply_silence_trim(pcm8, manifest, entry)
        pcm8 = apply_pcm8_edge_fade(pcm8)
        pcm8, note, sample_count = prepare_pcm_and_note(pcm8)
        dpcm_payload = get_or_encode_dpcm_payload(
            entry["clip_id"],
            pcm8,
            wav_path,
            gain_db,
            sample_rate,
            encoder_version,
            trim_silence,
            trim_threshold,
        )
        sym = symbol_for_clip(entry["clip_id"])
        song_index = len(songs_meta)
        song_id = song_id_base + song_index
        song_const = song_const_for_clip(entry["clip_id"])

        tone_index = voice_tone_indices[song_index]
        part_track = build_part_track(tone_index, note)

        song_entry = {
            "clip_id": entry["clip_id"],
            "symbol": sym,
            "song_const": song_const,
            "song_id": song_id,
            "song_index": song_index,
            "tone_index": tone_index,
            "part_track": part_track,
            "title": entry.get("title", entry["clip_id"])[:23],
            "sample_count": sample_count,
            "wave_bytes": dpcm_wave_bytes_for(sample_count),
            "wav_rel": entry["wav"],
            "trigger": trigger,
        }
        if "turn_text" in entry:
            song_entry["turn_text"] = entry["turn_text"]
        songs_meta.append(song_entry)
        dpcm_blobs.append(dpcm_payload)

        turn_text_ref = (
            turn_text_symbol_for(sym) if "turn_text" in entry else "NULL"
        )

        for card_target in resolve_card_targets(entry.get("card_id", "CARD_NONE"), card_ids):
            for target in resolve_duelist_targets(entry["duelist"], ai_ids, opponent_ids):
                clips_meta.append(
                    {
                        "song_const": song_const,
                        "song_id": song_id,
                        "duelist_id": target["voice_id"],
                        "opponent_id": target["opponent_id"],
                        "duelist_ref": target["ref"],
                        "card_id": card_target["card_id"],
                        "lp_threshold": entry.get("lp_threshold", 0),
                        "trigger_type": f"CUSTOM_VOICE_TRIGGER_{trigger.upper()}",
                        "priority": entry.get("priority", 0),
                        "replace_vanilla": 1 if entry.get("replace_vanilla", False) else 0,
                        "song_index": song_index,
                        "turn_text_ref": turn_text_ref,
                    }
                )

    out_dir = args.out_dir
    out_dir.mkdir(parents=True, exist_ok=True)

    voice_rom_bytes = sum(meta["wave_bytes"] + 3 for meta in songs_meta)
    voice_rom_bytes += len(songs_meta) * (18 + 12)
    tail_rom_budget = MAX_ROM_LIMIT - VOICE_PCM_ROM_ORG
    voice_rom_limit = tail_rom_budget - APPEND_ROM_RESERVE
    if voice_rom_bytes > voice_rom_limit:
        raise SystemExit(
            f"voice_pcm_rom overflow: {voice_rom_bytes} bytes used, "
            f"{voice_rom_limit} bytes available in tail ROM "
            f"(budget {tail_rom_budget} minus {APPEND_ROM_RESERVE} reserved for append)"
        )

    assets_s = render_assets_s(songs_meta, dpcm_blobs)
    triggers_inc = render_triggers_inc(clips_meta)
    turn_text_inc = render_turn_text_inc(songs_meta)
    debug_inc = render_debug_inc(songs_meta)
    header = render_header(manifest, songs_meta, clips_meta)
    rom_patches_json = render_rom_patches_json(songs_meta)
    song_headers_inc = render_song_headers_inc(songs_meta)
    wave_loader_inc = render_wave_loader_inc(songs_meta)
    inventory_md = render_voice_inventory_md(manifest, songs_meta)

    outputs = {
        out_dir / "voice_assets_generated.s": assets_s,
        out_dir / "voice_triggers_generated.inc": triggers_inc,
        out_dir / "voice_turn_text_generated.inc": turn_text_inc,
        out_dir / "voice_wave_loader_generated.inc": wave_loader_inc,
        out_dir / "debug_menu_voice_custom.inc": debug_inc,
        out_dir / "voice_song_headers_generated.inc": song_headers_inc,
        out_dir / "voice_rom_patches.json": rom_patches_json,
        HEADER: header,
        VOICE_INVENTORY_MD: inventory_md,
    }

    write_outputs(outputs)

    if args.stamp:
        args.stamp.parent.mkdir(parents=True, exist_ok=True)
        args.stamp.write_text(digest + "\n")


if __name__ == "__main__":
    main()
