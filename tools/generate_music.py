#!/usr/bin/env python3
import argparse
import hashlib
import html
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(Path(__file__).resolve().parent))
import generate_voices as gv  # noqa: E402

ASSETS = ROOT / "src_custom/assets/music"
MUSIC_INVENTORY_MD = ASSETS / "MUSIC.md"
GENERATED = ROOT / "src_custom/generated"
HEADER = ROOT / "include/constants/custom_music_generated.h"
VOICE_HEADER = ROOT / "include/constants/custom_voices_generated.h"
VOICE_PATCHES = ROOT / "src_custom/generated/voice_rom_patches.json"
VOICE_INVENTORY = ROOT / "src_custom/assets/voices/VOICES.md"

M4A_BGM_PART_TEMPO = gv.M4A_VOICE_PART_TEMPO
M4A_BGM_PART_VOLUME = 0x7F
M4A_BGM_PRIORITY = 20
M4A_BGM_PLAYER = 0
M4A_BGM_SONG_MODE = 1
M4A_BGM_SONG_PLAYER = 0x00000000
M4A_BGM_NOTE_KEY = gv.M4A_VOICE_NOTE_KEY
M4A_BGM_NOTE_VEL = gv.M4A_VOICE_NOTE_VEL
MUSIC_DEFAULT_GAIN_DB = 4.0
MUSIC_PCM8_TARGET_PEAK = 124
# ponytail: long WAV BGM is one tied note; no frame hook or streaming state.
MAX_NOTE_SAMPLE_CAPACITY = None  # filled by max_note_sample_capacity() on first use
MUSIC_CODEC_PCM8 = "pcm8"
MUSIC_CODEC_DPCM = "dpcm"


def symbol_for_track(track_id: str) -> str:
    safe = re.sub(r"[^A-Za-z0-9_]", "_", track_id)
    if safe[0].isdigit():
        safe = f"m_{safe}"
    return safe


def song_const_for_track(track_id: str) -> str:
    return f"MUSIC_CUSTOM_{symbol_for_track(track_id).upper()}"


def default_song_id_base() -> int:
    if VOICE_HEADER.is_file():
        match = re.search(r"#define CUSTOM_VOICE_SONG_ID_MAX (\d+)", VOICE_HEADER.read_text())
        if match:
            return int(match.group(1)) + 1
    return 652


def load_reserved_tone_indices() -> set[int]:
    used = set()
    if VOICE_PATCHES.is_file():
        data = json.loads(VOICE_PATCHES.read_text())
        for entry in data.get("tone_patches", []):
            used.add((entry["org"] - gv.M4A_TONE_TABLE_ORG) // 12)
    used.update(gv.layout_forbidden_tone_indices())
    return used


def allocate_music_tone_indices(num_segments: int, reserved_tones: set[int]) -> list[int]:
    """Pick tone slots in the custom voice range without clobbering vanilla tones <128."""
    forbidden = set(reserved_tones)
    forbidden.add(gv.M4A_VANILLA_DUEL_VOICE_TONE)
    forbidden.update(gv.layout_forbidden_tone_indices())
    for i in range(gv.M4A_VOICE_TONE_PREFER_MIN):
        forbidden.add(i)

    voice_tones = {
        (entry["org"] - gv.M4A_TONE_TABLE_ORG) // 12
        for entry in json.loads(VOICE_PATCHES.read_text()).get("tone_patches", [])
    } if VOICE_PATCHES.is_file() else set()
    prefer_min = max(gv.M4A_VOICE_TONE_PREFER_MIN, max(voice_tones, default=0) + 1)

    unused_tail = sorted(
        i
        for i in range(gv.M4A_TONE_INDEX_LAYOUT_MAX + 1)
        if i not in forbidden and i >= prefer_min
    )
    unused_gaps = sorted(
        i
        for i in range(gv.M4A_VOICE_TONE_PREFER_MIN, prefer_min)
        if i not in forbidden
    )
    chosen = (unused_gaps + unused_tail)[:num_segments]
    if len(chosen) < num_segments:
        raise SystemExit(
            f"need {num_segments} free m4a tone slots for custom music, "
            f"only {len(chosen)} unused in range "
            f"{gv.M4A_VOICE_TONE_PREFER_MIN}-{gv.M4A_TONE_INDEX_LAYOUT_MAX}; "
            f"raise MAX_SEGMENT_SAMPLES or drop tracks"
        )
    return chosen


def build_bgm_part_note(cmd, gate, extra=None):
    note = bytes([cmd, M4A_BGM_NOTE_KEY, M4A_BGM_NOTE_VEL, gate])
    if extra is not None:
        note += bytes([extra])
    return note


def encode_bgm_part_track_note(sample_count: int) -> bytes:
    if sample_count <= 0:
        raise SystemExit(f"music segment has no PCM samples ({sample_count})")
    return gv.encode_part_track_note(sample_count)


def part_track_tail(note: bytes) -> bytes:
    if len(note) == 5:
        return bytes([0xB1, 0x00, 0x00, 0x01, 0x00])
    return bytes([0xB1, 0x00, 0x00, 0x00, 0x01, 0x00])


def max_note_sample_capacity() -> int:
    global MAX_NOTE_SAMPLE_CAPACITY
    if MAX_NOTE_SAMPLE_CAPACITY is not None:
        return MAX_NOTE_SAMPLE_CAPACITY

    lo, hi = 1, 400000
    best = 1
    while lo <= hi:
        mid = (lo + hi) // 2
        try:
            note = gv.encode_part_track_note(mid)
            extra = note[4] if len(note) == 5 else None
            cap = int(gv.estimate_note_sample_capacity(note[0], note[3], extra))
            if cap >= mid:
                best = mid
                lo = mid + 1
            else:
                hi = mid - 1
        except SystemExit:
            hi = mid - 1
    MAX_NOTE_SAMPLE_CAPACITY = best
    return best


def plan_note_gates(total_samples: int) -> list[bytes]:
    if total_samples <= 0:
        raise SystemExit(f"music track has no PCM samples ({total_samples})")
    max_gate = max_note_sample_capacity()
    notes: list[bytes] = []
    remaining = total_samples
    while remaining > 0:
        chunk = min(remaining, max_gate)
        notes.append(encode_bgm_part_track_note(chunk))
        remaining -= chunk
    return notes


def split_music_pcm_segments(pcm8: bytes) -> list[bytes]:
    max_gate = max_note_sample_capacity()
    return [pcm8[i : i + max_gate] for i in range(0, len(pcm8), max_gate)]


def wait_command_for_ticks(ticks: int) -> int:
    for idx in range(len(gv.M4A_NOTE_LENGTH_TABLE) - 1, -1, -1):
        if gv.M4A_NOTE_LENGTH_TABLE[idx] <= ticks:
            return 0x81 + idx
    raise ValueError(f"cannot encode wait for {ticks} ticks")


def build_wait_commands(total_ticks: int) -> bytes:
    waits = bytearray()
    remaining = total_ticks
    while remaining > 0:
        cmd = wait_command_for_ticks(remaining)
        waits.append(cmd)
        remaining -= gv.M4A_NOTE_LENGTH_TABLE[cmd - 0x81]
    return bytes(waits)


def music_wait_ticks_for_samples(sample_count: int) -> int:
    if sample_count <= 0:
        raise SystemExit(f"music track has no PCM samples ({sample_count})")
    return max(1, int(round(sample_count / gv.M4A_NOTE_CAPACITY_A)))


def build_bgm_tie_part_track_size(wait_count: int, loop: bool) -> int:
    return 8 + 3 + wait_count + 2 + (5 if loop else 0) + 1


def build_bgm_part_track_continuous(tone_index: int, notes: list[bytes], loop: bool) -> bytes:
    part = bytearray([0xBC, 0x00, 0xBB, M4A_BGM_PART_TEMPO])
    loop_start = len(part)
    part.extend([0xBD, tone_index, 0xBE, M4A_BGM_PART_VOLUME])
    for note in notes:
        part.extend(note)
    if loop:
        jump_pos = len(part)
        offset = loop_start - (jump_pos + 3)
        if offset < -32768 or offset > 32767:
            raise SystemExit(
                f"loop jump out of range ({offset}); shorten track or split manifest"
            )
        part.extend([0xDC, offset & 0xFF, (offset >> 8) & 0xFF])
    part.extend(part_track_tail(notes[-1]))
    return bytes(part)


def build_bgm_part_track(segments: list[tuple[int, bytes]], loop: bool) -> bytes:
    """Test helper: legacy multi-tone segment layout."""
    part = bytearray([0xBC, 0x00, 0xBB, M4A_BGM_PART_TEMPO])
    loop_start = len(part)
    for tone_index, note in segments:
        part.extend([0xBD, tone_index, 0xBE, M4A_BGM_PART_VOLUME])
        part.extend(note)
    if loop:
        jump_pos = len(part)
        offset = loop_start - (jump_pos + 3)
        if offset < -32768 or offset > 32767:
            raise SystemExit(f"loop jump out of range ({offset})")
        part.extend([0xDC, offset & 0xFF, (offset >> 8) & 0xFF])
    part.extend(part_track_tail(segments[-1][1]))
    return bytes(part)


def parse_voice_inventory_rom_bytes() -> int:
    if not VOICE_INVENTORY.is_file():
        return 0
    text = VOICE_INVENTORY.read_text()
    match = re.search(
        r"<td><strong>Total</strong></td>\s*<td>[^<]*</td>\s*<td><strong>([^<]+)</strong>",
        text,
    )
    if not match:
        return 0
    raw = match.group(1).strip()
    if raw.endswith(" B"):
        return int(raw[:-2].replace(",", ""))
    kb_match = re.match(r"([\d,]+) B", raw)
    if kb_match:
        return int(kb_match.group(1).replace(",", ""))
    return 0


def pcm_wave_bytes_for(sample_count: int) -> int:
    return 16 + sample_count


def music_codec_for(manifest, entry) -> str:
    codec = str(entry.get("codec", manifest.get("codec", MUSIC_CODEC_DPCM))).lower()
    if codec not in (MUSIC_CODEC_PCM8, MUSIC_CODEC_DPCM):
        raise SystemExit(f"{entry['track_id']}: unsupported music codec {codec!r}")
    return codec


def music_wave_payload_for(codec: str, pcm8: bytes) -> bytes:
    if codec == MUSIC_CODEC_DPCM:
        return gv.encode_dpcm_pcm8_validated(pcm8)
    return pcm8


def music_wave_type_for(codec: str) -> int:
    if codec == MUSIC_CODEC_DPCM:
        return gv.M4A_WAVE_TYPE_DPCM
    return gv.M4A_WAVE_TYPE_PCM


def music_wave_bytes_for(codec: str, sample_count: int, payload_len: int) -> int:
    wave_bytes = 16 + payload_len
    if wave_bytes & 1:
        wave_bytes += 1
    return wave_bytes


def resolve_music_trim_settings(manifest, entry):
    enabled = entry.get("trim_silence", manifest.get("trim_silence", False))
    threshold = entry.get(
        "trim_silence_threshold",
        manifest.get("trim_silence_threshold", gv.PCM8_SILENCE_TRIM_THRESHOLD),
    )
    return bool(enabled), int(threshold)


def apply_music_silence_trim(pcm8, manifest, entry):
    enabled, threshold = resolve_music_trim_settings(manifest, entry)
    if not enabled:
        return pcm8
    return gv.trim_silence_edges_pcm8(pcm8, threshold)


def resolve_music_gain_db(manifest, entry):
    return float(entry.get("gain_db", manifest.get("gain_db", MUSIC_DEFAULT_GAIN_DB)))


def apply_gain_db_pcm8(pcm8: bytes, gain_db: float) -> bytes:
    if not gain_db:
        return pcm8
    scale = 10 ** (gain_db / 20)
    return gv.signed_samples_to_pcm8(
        max(-128, min(127, int(round(gv.pcm8_sample_value(byte) * scale))))
        for byte in pcm8
    )


def peak_normalize_pcm8(pcm8: bytes, target_peak: int = MUSIC_PCM8_TARGET_PEAK) -> bytes:
    peak = max(abs(gv.pcm8_sample_value(byte)) for byte in pcm8) or 1
    if peak == target_peak:
        return pcm8
    scale = target_peak / peak
    return gv.signed_samples_to_pcm8(
        max(-128, min(127, int(round(gv.pcm8_sample_value(byte) * scale))))
        for byte in pcm8
    )


def prepare_music_pcm8(wav_path, sample_rate, manifest, entry):
    gain_db = resolve_music_gain_db(manifest, entry)
    pcm8, rate = gv.read_wav_mono_pcm8(wav_path, sample_rate, 0.0)
    pcm8 = apply_music_silence_trim(pcm8, manifest, entry)
    pcm8 = apply_gain_db_pcm8(pcm8, gain_db)
    pcm8 = peak_normalize_pcm8(pcm8)
    pcm8 = gv.apply_pcm8_edge_fade(pcm8, fade_samples=48)
    return pcm8, rate


def validate_track(entry, sample_rate, manifest=None):
    track_id = entry["track_id"]
    wav_rel = entry["wav"]
    wav_path = ASSETS / wav_rel
    if not wav_path.is_file():
        raise SystemExit(f"{track_id}: missing WAV {wav_path}")
    if manifest is not None:
        pcm8, rate = prepare_music_pcm8(wav_path, sample_rate, manifest, entry)
    else:
        pcm8, rate = gv.read_wav_mono_pcm8(wav_path, sample_rate, entry.get("gain_db", 0.0))
        pcm8 = gv.apply_pcm8_edge_fade(pcm8, fade_samples=48)
    if rate != sample_rate:
        raise SystemExit(f"{track_id}: resample failed")
    if not pcm8:
        raise SystemExit(f"{track_id}: empty audio after preprocessing")


def render_music_rom_s(tracks_meta, payload_by_track):
    lines = [
        "@ Custom BGM WaveData + m4a part tracks + SongHeaders in main ROM tail.",
        f"@ Source PCM is mono @ {gv.M4A_WAVE_SAMPLE_RATE} Hz; long tracks use one tied note.",
        f"@ WaveData.freq uses 0x{gv.M4A_WAVE_FREQ:08X}.",
        ".section .music_pcm_rom",
        ".align 4",
        "",
    ]
    for meta in tracks_meta:
        sym = meta["symbol"]
        payload = payload_by_track[sym]
        lines.append(f".global CustomMusic_{sym}_Wave")
        lines.append(f"CustomMusic_{sym}_Wave:")
        lines.append(f"    .hword {meta['wave_type']}, 0")
        lines.append(f"    .word 0x{gv.M4A_WAVE_FREQ:08X}")
        lines.append("    .word 0")
        lines.append(f"    .word {meta['sample_count']}")
        byte_lines = [f"0x{b:02X}" for b in payload]
        for i in range(0, len(byte_lines), 16):
            chunk = byte_lines[i : i + 16]
            lines.append(f"    .byte {', '.join(chunk)}")
        lines.append(".align 4")
        lines.append("")

        wait_bytes = ", ".join(f"0x{b:02X}" for b in meta["wait_commands"])
        lines.append(f".global CustomMusic_{sym}_Part")
        lines.append(f"CustomMusic_{sym}_Part:")
        lines.append(
            f"    .byte 0xBC, 0x00, 0xBB, {M4A_BGM_PART_TEMPO}, "
            f"0xBD, {meta['tone_index']}, 0xBE, {M4A_BGM_PART_VOLUME}"
        )
        lines.append(f"CustomMusic_{sym}_LoopStart:")
        lines.append(f"    .byte 0xCF, {M4A_BGM_NOTE_KEY}, {M4A_BGM_NOTE_VEL}")
        lines.append(f"    .byte {wait_bytes}")
        lines.append(f"    .byte 0xCE, {M4A_BGM_NOTE_KEY}")
        if meta["loop"]:
            lines.append("    .byte 0xB2")
            lines.append(f"    .word CustomMusic_{sym}_LoopStart")
        lines.append("    .byte 0xB1")
        lines.append(".align 4")
        lines.append("")
        lines.append(f".global CustomMusic_{sym}_SongHeader")
        lines.append(f"CustomMusic_{sym}_SongHeader:")
        lines.append(
            f"    .byte 1, 0, {M4A_BGM_PRIORITY}, 0  @ trackCount, blockCount, priority, reverb"
        )
        lines.append(f"    .word 0x{gv.M4A_TONE_GROUP_PTR:08X}  @ tone group")
        lines.append(f"    .word CustomMusic_{sym}_Part")
        lines.append(".align 4")
        lines.append("")
    return "\n".join(lines) + "\n"


def render_stream_inc(tracks_meta):
    return "@ Custom BGM uses ordinary m4a song data; no runtime stream table.\n"


def render_header(manifest, tracks_meta):
    song_id_base = manifest["song_id_base"]
    lines = [
        "#ifndef GUARD_CUSTOM_MUSIC_GENERATED_H",
        "#define GUARD_CUSTOM_MUSIC_GENERATED_H",
        "",
        f"#define CUSTOM_MUSIC_SONG_COUNT {len(tracks_meta)}",
        f"#define CUSTOM_MUSIC_SONG_ID_MIN {song_id_base}",
    ]
    if tracks_meta:
        lines.append(
            f"#define CUSTOM_MUSIC_SONG_ID_MAX {song_id_base + len(tracks_meta) - 1}"
        )
    else:
        lines.append(f"#define CUSTOM_MUSIC_SONG_ID_MAX {song_id_base}")
    lines.append("")
    for meta in tracks_meta:
        lines.append(f"#define {meta['song_const']} {meta['song_id']}")
    lines.append("")
    lines.append("void PlayCustomMusic(u8 songIndex);")
    lines.append("void PlayCustomMusicById(u16 songId);")
    lines.append("")
    lines.append("#endif // GUARD_CUSTOM_MUSIC_GENERATED_H")
    lines.append("")
    return "\n".join(lines)


def render_rom_patches_json(tracks_meta):
    tone_patches = []
    song_patches = []
    mode_patches = []
    for meta in tracks_meta:
        sym = meta["symbol"]
        org = gv.M4A_TONE_TABLE_ORG + meta["tone_index"] * 12
        gv.assert_tone_patch_org_safe(org, f"music tone {meta['tone_index']} for {meta['track_id']}")
        tone_patches.append(
            {
                "org": org,
                "wave_symbol": f"CustomMusic_{sym}_Wave",
            }
        )
        song_patches.append(
            {
                "org": gv.M4A_SONG_TABLE_ORG + meta["song_id"] * 8,
                "header_symbol": f"CustomMusic_{sym}_SongHeader",
                "player": M4A_BGM_SONG_PLAYER,
            }
        )
        mode_patches.append(
            {
                "org": gv.M4A_SONG_MODE_TABLE_ORG + meta["song_id"],
                "mode": M4A_BGM_SONG_MODE,
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


def render_debug_inc(tracks_meta):
    lines = []
    for meta in tracks_meta:
        title = meta["title"].replace('"', '\\"')
        lines.append(f'DEBUG_MENU_MUSIC_ENTRY({meta["song_const"]}, "{title}")')
    return "\n".join(lines) + ("\n" if lines else "")


def format_byte_size(num_bytes: int) -> str:
    if num_bytes < 1024:
        return f"{num_bytes} B"
    return f"{num_bytes:,} B ({num_bytes / 1024:.1f} KB)"


def render_music_inventory_md(manifest, tracks_meta):
    registered = {meta["wav_rel"] for meta in tracks_meta}
    orphan_wavs = sorted(
        path.relative_to(ASSETS).as_posix()
        for path in ASSETS.rglob("*.wav")
        if path.relative_to(ASSETS).as_posix() not in registered
    )
    lines = [
        "# Custom Music Asset Inventory",
        "",
        "Auto-generated by [`tools/generate_music.py`](../../tools/generate_music.py) when you run `make`.",
        "",
        "## Registered tracks",
        "",
        "<table>",
        "  <thead>",
        "    <tr>",
        "      <th>Title</th>",
        "      <th>WAV</th>",
        "      <th>Codec</th>",
        "      <th>Duration</th>",
        "      <th>Notes</th>",
        "      <th>Source WAV</th>",
        "      <th>In-ROM</th>",
        "    </tr>",
        "  </thead>",
        "  <tbody>",
    ]
    if tracks_meta:
        total_source = 0
        total_rom = 0
        for meta in tracks_meta:
            wav_path = ASSETS / meta["wav_rel"]
            source_bytes = wav_path.stat().st_size if wav_path.is_file() else 0
            total_source += source_bytes
            total_rom += meta["rom_bytes"]
            duration = meta["sample_count"] / manifest.get("sample_rate", gv.M4A_WAVE_SAMPLE_RATE)
            lines.append(
                "    <tr>"
                f"<td>{html.escape(meta['title'])}</td>"
                f"<td><code>{html.escape(meta['wav_rel'])}</code></td>"
                f"<td>{html.escape(meta['codec'])}</td>"
                f"<td>{duration:.1f}s</td>"
                f"<td>{meta['note_count']}</td>"
                f"<td>{format_byte_size(source_bytes)}</td>"
                f"<td>{format_byte_size(meta['rom_bytes'])}</td>"
                "</tr>"
            )
        lines.append(
            "    <tr>"
            '<td colspan="5"><strong>Total</strong></td>'
            f"<td><strong>{format_byte_size(total_source)}</strong></td>"
            f"<td><strong>{format_byte_size(total_rom)}</strong></td>"
            "</tr>"
        )
    else:
        lines.append('    <tr><td colspan="7"><em>none</em></td></tr>')
    lines.extend(["  </tbody>", "</table>"])
    if orphan_wavs:
        lines.extend(
            [
                "",
                "## Unregistered WAVs",
                "",
                "These files exist under `src_custom/assets/music/` but are not listed in the manifest:",
                "",
            ]
        )
        for wav_rel in orphan_wavs:
            wav_path = ASSETS / wav_rel
            lines.append(f"- `{wav_rel}` ({format_byte_size(wav_path.stat().st_size)})")
    lines.append("")
    return "\n".join(lines)


def iter_music_wav_paths():
    if not ASSETS.is_dir():
        return []
    return sorted(ASSETS.rglob("*.wav"))


def compute_music_inputs_digest(manifest_path: Path, generator_path: Path) -> str:
    hasher = hashlib.sha256()
    gv.file_stat_digest(manifest_path.resolve(), hasher)
    gv.file_stat_digest(generator_path.resolve(), hasher)
    if VOICE_PATCHES.is_file():
        gv.file_stat_digest(VOICE_PATCHES, hasher)
    for wav_path in iter_music_wav_paths():
        gv.file_stat_digest(wav_path.relative_to(ROOT), hasher)
        hasher.update(wav_path.read_bytes())
    return hasher.hexdigest()


def write_outputs(outputs: dict[Path, str]) -> None:
    for path, content in outputs.items():
        path.parent.mkdir(parents=True, exist_ok=True)
        if not path.exists() or path.read_text() != content:
            path.write_text(content)
            print(f"WROTE {path.relative_to(ROOT)}")
        else:
            print(f"OK    {path.relative_to(ROOT)}")


def render_empty_outputs(manifest, out_dir: Path):
    song_id_base = manifest.get("song_id_base") or default_song_id_base()
    manifest = {**manifest, "song_id_base": song_id_base}
    outputs = {
        out_dir / "music_assets_generated.s": (
            ".section .music_pcm_rom\n.align 4\n"
            "@ No custom music tracks registered.\n"
        ),
        out_dir / "music_rom_patches.json": render_rom_patches_json([]),
        out_dir / "debug_menu_music_custom.inc": "",
        out_dir / "music_stream_generated.inc": "",
        HEADER: render_header(manifest, []),
        MUSIC_INVENTORY_MD: render_music_inventory_md(manifest, []),
    }
    write_outputs(outputs)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("manifest", type=Path)
    parser.add_argument("--out-dir", type=Path, default=GENERATED)
    parser.add_argument("--stamp", type=Path, default=None)
    args = parser.parse_args()

    generator_path = Path(__file__).resolve()
    digest = compute_music_inputs_digest(args.manifest, generator_path)
    if args.stamp and gv.stamp_is_current(args.stamp, digest):
        return

    manifest = json.loads(args.manifest.read_text())
    sample_rate = manifest.get("sample_rate", gv.M4A_WAVE_SAMPLE_RATE)
    song_id_base = manifest.get("song_id_base") or default_song_id_base()
    if song_id_base <= 0:
        song_id_base = default_song_id_base()
    manifest["song_id_base"] = song_id_base
    tracks = manifest.get("tracks", [])

    if not tracks:
        render_empty_outputs(manifest, args.out_dir)
        if args.stamp:
            args.stamp.parent.mkdir(parents=True, exist_ok=True)
            args.stamp.write_text(digest + "\n")
        return

    reserved_tones = load_reserved_tone_indices()
    tracks_meta = []
    payload_by_track: dict[str, bytes] = {}

    staged: list[tuple[dict, bytes]] = []
    for entry in tracks:
        validate_track(entry, sample_rate, manifest)
        wav_path = ASSETS / entry["wav"]
        pcm8, _ = prepare_music_pcm8(wav_path, sample_rate, manifest, entry)
        staged.append((entry, pcm8))

    tone_indices = allocate_music_tone_indices(len(staged), reserved_tones)

    for (entry, pcm8), tone_index in zip(staged, tone_indices):
        sym = symbol_for_track(entry["track_id"])
        codec = music_codec_for(manifest, entry)
        payload = music_wave_payload_for(codec, pcm8)
        song_index = len(tracks_meta)
        song_id = song_id_base + song_index
        if song_id >= 800:
            raise SystemExit(
                f"song id {song_id} for {entry['track_id']} exceeds PlayMusic limit (<800)"
            )

        sample_count = len(pcm8)
        wait_ticks = music_wait_ticks_for_samples(sample_count)
        wait_commands = build_wait_commands(wait_ticks)
        loop = entry.get("loop", True)
        tracks_meta.append(
            {
                "track_id": entry["track_id"],
                "symbol": sym,
                "song_const": song_const_for_track(entry["track_id"]),
                "song_id": song_id,
                "song_index": song_index,
                "title": entry.get("title", entry["track_id"])[:23],
                "wav_rel": entry["wav"],
                "codec": codec,
                "wave_type": music_wave_type_for(codec),
                "sample_count": sample_count,
                "payload_bytes": len(payload),
                "note_count": 1,
                "wait_ticks": wait_ticks,
                "wait_commands": wait_commands,
                "tone_index": tone_index,
                "loop": loop,
                "rom_bytes": (
                    music_wave_bytes_for(codec, sample_count, len(payload))
                    + build_bgm_tie_part_track_size(len(wait_commands), loop)
                    + 12
                ),
            }
        )
        payload_by_track[sym] = payload

    music_rom_bytes = sum(meta["rom_bytes"] for meta in tracks_meta)
    voice_rom_bytes = parse_voice_inventory_rom_bytes()
    tail_budget = gv.MAX_ROM_LIMIT - gv.VOICE_PCM_ROM_ORG
    rom_limit = tail_budget - gv.APPEND_ROM_RESERVE
    combined = music_rom_bytes + voice_rom_bytes
    if combined > rom_limit:
        raise SystemExit(
            f"audio_pcm_rom overflow: music {music_rom_bytes} + voice {voice_rom_bytes} = "
            f"{combined} bytes, limit {rom_limit}"
        )

    out_dir = args.out_dir
    outputs = {
        out_dir / "music_assets_generated.s": render_music_rom_s(tracks_meta, payload_by_track),
        out_dir / "music_rom_patches.json": render_rom_patches_json(tracks_meta),
        out_dir / "music_stream_generated.inc": render_stream_inc(tracks_meta),
        out_dir / "debug_menu_music_custom.inc": render_debug_inc(tracks_meta),
        HEADER: render_header(manifest, tracks_meta),
        MUSIC_INVENTORY_MD: render_music_inventory_md(manifest, tracks_meta),
    }
    write_outputs(outputs)

    if args.stamp:
        args.stamp.parent.mkdir(parents=True, exist_ok=True)
        args.stamp.write_text(digest + "\n")


if __name__ == "__main__":
    main()
