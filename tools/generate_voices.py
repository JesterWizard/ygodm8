#!/usr/bin/env python3
import argparse
import audioop
import hashlib
import html
import json
import re
import struct
import wave
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
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
CUSTOM_VOICE_TONE_INDEX_BASE = 48
CUSTOM_VOICE_PART_SIZE = 18
CUSTOM_VOICE_WAVE_HEADER_SIZE = 16

# Tail ROM: voice PCM @ VOICE_PCM_ROM_ORG, then append (code/assets). See ldscript.ld + validate_lynjump.
VOICE_PCM_ROM_ORG = 0x08FE3400
MAX_ROM_LIMIT = 0x0A000000
# Reserve headroom for appended code/assets (~768 KiB; current append ~660 KiB).
APPEND_ROM_RESERVE = 0x000C0000

# (vanilla_pcm_samples, note bytes before 0xB1). From baserom duel voice part tracks.
# Each note encodes a fixed playback length equal to its sample count. Pick the largest
# reference still <= the clip, then pad up to the next bracket whenever the clip is
# longer than that note (never pick a longer reference without padding — that makes m4a
# read past the WaveData buffer and play silence).
PART_TRACK_NOTE_BY_SAMPLES = (
    (14123, bytes([0xDA, 0x3C, 0x7F, 0x8B])),
    (19368, bytes([0xE0, 0x3C, 0x7F, 0x91])),
    (22762, bytes([0xE1, 0x3C, 0x7F, 0x92])),
    (40580, bytes([0xE9, 0x3C, 0x7F, 0x9A, 0x81])),
    (44608, bytes([0xEB, 0x3C, 0x7F, 0x9C])),
    (50870, bytes([0xEC, 0x3C, 0x7F, 0x9D])),
    (53937, bytes([0xED, 0x3C, 0x7F, 0x9E])),
)
# Normalize all clips to this 16-bit peak before 8-bit conversion (32767 ≈ full s8 range).
PCM8_TARGET_PEAK = 32767

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
        frames = audioop.mul(frames, sample_width, PCM8_TARGET_PEAK / peak)

    pcm8 = audioop.lin2lin(frames, sample_width, 1)
    return pcm8, target_rate


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


def validate_clip(entry, ai_ids, opponent_ids, card_ids, sample_rate):
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


def note_bytes_for_sample_count(sample_count):
    best = PART_TRACK_NOTE_BY_SAMPLES[0][1]
    for threshold, note in PART_TRACK_NOTE_BY_SAMPLES:
        if sample_count >= threshold:
            best = note
        else:
            break
    return best


def prepare_pcm_and_note(pcm8):
    sample_count = len(pcm8)
    ref_index = 0
    for i, (threshold, _note) in enumerate(PART_TRACK_NOTE_BY_SAMPLES):
        if sample_count >= threshold:
            ref_index = i
        else:
            break

    ref_threshold, note = PART_TRACK_NOTE_BY_SAMPLES[ref_index]
    if sample_count > ref_threshold and ref_index + 1 < len(PART_TRACK_NOTE_BY_SAMPLES):
        next_threshold, next_note = PART_TRACK_NOTE_BY_SAMPLES[ref_index + 1]
        pcm8 = pcm8 + bytes(next_threshold - sample_count)
        note = next_note
        sample_count = next_threshold

    return pcm8, note, sample_count


def part_track_tail(note):
    if len(note) == 5:
        return bytes([0xB1, 0x00, 0x00, 0x01, 0x00])
    return bytes([0xB1, 0x00, 0x00, 0x00, 0x01, 0x00])


def build_part_track(tone_index, note):
    part = bytearray(
        [0xBC, 0x00, 0xBB, 0x14, 0xBD, tone_index, 0xBE, 0x74]
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


def render_voice_rom_s(songs_meta, pcm_blobs):
    lines = [
        "@ Custom voice WaveData + m4a part tracks + SongHeaders in main ROM (0x08xxxxxx).",
        f"@ PCM is signed 8-bit mono @ {M4A_WAVE_SAMPLE_RATE} Hz; WaveData.freq uses 0x{M4A_WAVE_FREQ:08X}.",
        ".section .voice_pcm_rom",
        ".align 4",
        "",
    ]

    for meta, pcm in zip(songs_meta, pcm_blobs):
        sym = meta["symbol"]
        part = meta["part_track"]
        part_bytes = ", ".join(f"0x{b:02X}" for b in part)

        lines.append(f".global CustomVoice_{sym}_Wave")
        lines.append(f"CustomVoice_{sym}_Wave:")
        lines.append("    .hword 0, 0")
        lines.append(f"    .word 0x{M4A_WAVE_FREQ:08X}")
        lines.append("    .word 0")
        lines.append(f"    .word {meta['sample_count']}")
        byte_lines = [f"0x{b:02X}" for b in pcm]
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


def render_assets_s(songs_meta, pcm_blobs):
    return render_voice_rom_s(songs_meta, pcm_blobs)


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
    return ""


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
        "- **In-ROM** — m4a `WaveData` blob in main ROM: 16-byte header + 8-bit mono PCM (+ 1-byte pad if odd).",
        "- **Overall Change** — `(in-ROM − source) / source`; negative means the ROM blob is smaller.",
        "- **Total** row — sum of all registered clips (source vs in-ROM).",
        "",
        "## Registered clips",
        "",
        "<table>",
        "  <thead>",
        "    <tr>",
        "      <th align=\"center\">Title</th>",
        "      <th align=\"center\">WAV</th>",
        "      <th align=\"center\">Trigger</th>",
        "      <th align=\"center\">Source WAV</th>",
        "      <th align=\"center\">In-ROM</th>",
        "      <th align=\"center\">Overall Change</th>",
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
                f'<td align="center">{title}</td>'
                f'<td align="center"><code>{wav_rel}</code></td>'
                f'<td align="center"><code>{trigger}</code></td>'
                f'<td align="center">{format_byte_size(source_bytes)}</td>'
                f'<td align="center">{format_byte_size(rom_bytes)}</td>'
                f'<td align="center">{format_colored_size_delta(source_bytes, rom_bytes)}</td>'
                "</tr>"
            )
        lines.append(
            "    <tr>"
            '<td align="center" colspan="3"><strong>Total</strong></td>'
            f'<td align="center"><strong>{format_byte_size(total_source_bytes)}</strong></td>'
            f'<td align="center"><strong>{format_byte_size(total_rom_bytes)}</strong></td>'
            f'<td align="center"><strong>{format_colored_size_delta(total_source_bytes, total_rom_bytes)}</strong></td>'
            "</tr>"
        )
    else:
        lines.append('    <tr><td align="center" colspan="6"><em>none</em></td></tr>')

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
    args = parser.parse_args()

    generator_path = Path(__file__).resolve()
    digest = compute_voice_inputs_digest(args.manifest, generator_path)
    if args.stamp and stamp_is_current(args.stamp, digest):
        return

    manifest = json.loads(args.manifest.read_text())
    ai_ids = load_ai_duelist_ids()
    opponent_ids = load_opponent_ids()
    card_ids = load_card_ids()

    sample_rate = manifest.get("sample_rate", M4A_WAVE_SAMPLE_RATE)
    song_id_base = manifest["song_id_base"]
    clips = manifest.get("clips", [])

    if not clips:
        raise SystemExit("voice_manifest.json: clips array is empty")

    if CUSTOM_VOICE_TONE_INDEX_BASE + len(clips) > 200:
        raise SystemExit(
            f"too many custom voice clips for tone table slots "
            f"(max {200 - CUSTOM_VOICE_TONE_INDEX_BASE} starting at {CUSTOM_VOICE_TONE_INDEX_BASE})"
        )

    songs_meta = []
    clips_meta = []
    pcm_blobs = []

    for entry in clips:
        trigger = entry["trigger"]
        validate_clip(entry, ai_ids, opponent_ids, card_ids, sample_rate)

        wav_path = ASSETS / entry["wav"]
        gain_db = entry.get("gain_db", 0.0)
        pcm8, _ = read_wav_mono_pcm8(wav_path, sample_rate, gain_db)
        pcm8, note, sample_count = prepare_pcm_and_note(pcm8)
        sym = symbol_for_clip(entry["clip_id"])
        song_index = len(songs_meta)
        song_id = song_id_base + song_index
        song_const = song_const_for_clip(entry["clip_id"])

        tone_index = CUSTOM_VOICE_TONE_INDEX_BASE + song_index
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
            "wave_bytes": wave_bytes_for(sample_count),
            "wav_rel": entry["wav"],
            "trigger": trigger,
        }
        if "turn_text" in entry:
            song_entry["turn_text"] = entry["turn_text"]
        songs_meta.append(song_entry)
        pcm_blobs.append(pcm8)

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

    voice_rom_bytes = sum(wave_bytes_for(len(pcm)) + 3 for pcm in pcm_blobs)
    voice_rom_bytes += len(songs_meta) * (18 + 12)
    tail_rom_budget = MAX_ROM_LIMIT - VOICE_PCM_ROM_ORG
    voice_rom_limit = tail_rom_budget - APPEND_ROM_RESERVE
    if voice_rom_bytes > voice_rom_limit:
        raise SystemExit(
            f"voice_pcm_rom overflow: {voice_rom_bytes} bytes used, "
            f"{voice_rom_limit} bytes available in tail ROM "
            f"(budget {tail_rom_budget} minus {APPEND_ROM_RESERVE} reserved for append)"
        )

    assets_s = render_assets_s(songs_meta, pcm_blobs)
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
