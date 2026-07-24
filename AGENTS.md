# AGENTS.md

`ygodm8` is a GBA decompilation-style ROM hack of Yu-Gi-Oh! Forbidden Memories. See
[ARCHITECTURE.md](ARCHITECTURE.md) for layout, [SETUP.md](SETUP.md) for the toolchain, and
[documentation/tdd-framework.md](documentation/tdd-framework.md) for the test/lint commands.

## Cursor Cloud specific instructions

Toolchain (`arm-none-eabi`, `libpng`/`zlib` dev headers, `pkg-config`, Pillow) and a built
`agbcc` at `tools/agbcc/bin` are already present in the VM snapshot. The native `gbagfx`/`preproc`
helpers are compiled automatically by `make`. Standard commands live in
[SETUP.md](SETUP.md) / [documentation/tdd-framework.md](documentation/tdd-framework.md) — don't duplicate them here.

- **`baserom.gba` is required for the full ROM build and is intentionally not in the repo (copyrighted).**
  Place a clean retail Yu-Gi-Oh! Forbidden Memories GBA dump at the repo root. Without it, `make`
  fails at `data/data2.s` (which `.incbin`s regions from `baserom.gba`), and `make test`, UPS
  generation, and the voice-id / `event-validate` steps also fail. `make test-host` and compiling
  individual objects (e.g. `make build/src_custom/card_hooks.o`) work **without** it.
- **Fast dev loop is `make test-host`** (host Python tests + validators; no ROM link, no baserom).
  `make` / `make test` need `baserom.gba` and the full agbcc build.
- **Known pre-existing `make test-host` failures** (in-progress card work, not environment issues):
  ~13 assertion failures across specific card/effect tests, plus `test_voices.test_validate_clip_fixture`
  which fails only because it needs `baserom.gba`. Do not treat these as regressions from setup.
- **Rebuilding agbcc** (only if the snapshot copy is lost): the vendored `tools/agbcc` is missing
  `libc/arm/setjmp.s` and `libc/arm/trap.s` (fetch them from `github.com/pret/agbcc`), and its
  `gcc_arm` (`agbcc_arm`) does not compile under modern GCC. This repo only uses `agbcc` + `old_agbcc`,
  so build/install just `agbcc`, `old_agbcc`, `libgcc.a`, and `libc.a` and skip `agbcc_arm`.
