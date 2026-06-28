# Custom music assets

Place **WAV** files here, then register them in [`tools/music_manifest.json`](../../tools/music_manifest.json).

Example:

```text
src_custom/assets/music/overworld/my_theme.wav
```

```bash
make
```

Preview tracks in the overworld debug menu → **Music Viewer** (custom entries appear after vanilla OST rows).

See [`documentation/custom-music.md`](../../documentation/custom-music.md) for format, looping, and ROM limits.
