# ygodm8 — Repository Architecture

Yu-Gi-Oh! GBA decompilation-style ROM hack: inspect, modify, and rebuild the game from C and assembly. Vanilla logic stays in `src/`; all hack features live in `src_custom/` and are wired through LynJump hooks, Python generators, and manifest-driven data.

**Related docs:** [README.md](README.md) (build/setup), [CUSTOM_CONTENT.md](CUSTOM_CONTENT.md) (custom folder index), [documentation/](documentation/) (per-feature design notes), [SESSION_LOG.md](SESSION_LOG.md) (recent agent work).

---

## Index

- [Goals](#goals)
- [Mental model](#mental-model)
- [Top-level layout](#top-level-layout)
- [Where to look](#where-to-look)
- [Core systems](#core-systems)
- [Build and test](#build-and-test)
- [Agent workflow](#agent-workflow)

---

## Goals

| Goal | How the repo supports it |
|------|---------------------------|
| Understand vanilla behavior | `src/` mirrors decompiled ROM regions; symbols map to original functions |
| Add cards, effects, QoL | `src_custom/`, `tools/card_data_manifest.json`, `duel_helpers` API |
| Patch without editing vanilla | LynJump (`src_custom/LynJump.event` + `*_hooks.c` replacements) |
| Safe iteration | Host tests (`make test-host`), goldens, RAM map validation, optional full ROM link |
| Toggle custom work off | `CUSTOM_CODE=0`, `CUSTOM_EVENTS=0`, `CUSTOM_CARD_MANIFEST=0` in Makefile |

---

## Mental model

```
baserom.gba + vanilla (src/, asm/, data/)
        ↓
src_custom/ (hooks, effects, assets, generated/)
        ↓
tools/ (generators, validators, gbagfx, preproc) + agbcc
        ↓
ygodm8.gba  ← LynJump patches applied post-link
```

**Rule of thumb:** vanilla behavior → `src/` + `include/`; hack features → `src_custom/` + manifests; memory layout → `asm/ram_map.s`; runtime toggles → `configs/runtime.c`; validation → `tests/`.

---

## Top-level layout

| Path | Contains |
|------|----------|
| `src/` | Vanilla decompiled C. Do **not** add hack logic here. |
| `src_custom/` | All custom code, generated includes, assets, `LynJump.event`. |
| `include/` | Shared headers: `duel.h`, `card.h`, `duel_helpers.h`, `constants/`. |
| `asm/` | Boot, large ASM chunks, **`ram_map.s`** (RAM/Flash symbol placement). |
| `data/` | Static data assembly blobs. |
| `tools/` | Python generators/validators, `card_data_manifest.json`, native `gbagfx`/`preproc`. |
| `tests/` | Host unit tests (`tests/host/`), goldens, fixtures. |
| `configs/` | `runtime.c` — compile-time feature toggles and test-hand setup. |
| `documentation/` | Per-feature implementation docs (FogStages-style). |
| `events/` | Custom overworld event scripts. |
| `.agents/skills/` | Repeatable agent workflows (add card, LynJump, RAM map, etc.). |
| `build/` | Object files and intermediate art (generated, not hand-edited). |
| `generated/` | Linker fragments (`card_counts.ld`, memory-size includes). |

### `src_custom/` breakdown

| Subfolder | Purpose |
|-----------|---------|
| `*_hooks.c` | LynJump replacements and dispatch extensions (`duel_main_hooks.c`, `card_hooks.c`, …) |
| `spell_effects/`, `trap_effects/`, `activated_effects/`, `permanent_effects/`, `turn_effects/`, `battle_effects/` | Card effect bodies (one file per card when non-trivial) |
| `spell_effect_hooks.c`, `trap_effect_hooks.c`, `monster_effect_hooks.c`, … | Wire effect bodies into vanilla dispatch tables |
| `duel_helpers.c` | Reusable duel API (draw, destroy, LP change, summons, stat overlays) |
| `assets/cards/`, `assets/portraits/`, `assets/voices/` | Source art and audio |
| `generated/` | Build output — edit via manifests/scripts, not by hand |
| `custom_decks/`, `persist/`, `debug/` | Decks, save persistence, debug menus |

---

## Where to look

| I want to… | Start here |
|------------|------------|
| Add a custom card | `.agents/skills/add-custom-card/SKILL.md` → `tools/card_data_manifest.json` |
| Add a card effect | `.agents/skills/card-effect-hook-placement/SKILL.md` → `src_custom/*_effects/` |
| Replace a vanilla function | `.agents/skills/vanilla-function-replacements/SKILL.md` → `src_custom/*_hooks.c` + `LynJump.event` |
| Allocate RAM / save fields | `documentation/ram-map.md` → `asm/ram_map.s` |
| Change duel stat display | `src_custom/card_hooks.c` (`ApplyFieldZoneStatsToCardInfo`, `SetFinalStat__Replacement`) |
| Change field ATK/DEF tiles | `src_custom/mini_card_hooks.c` |
| Reusable effect logic (LP, draw, destroy) | `include/duel_helpers.h`, `src_custom/duel_helpers.c` |
| Runtime test setup (cards in hand) | `configs/runtime.c` |
| Card IDs and constants | `include/constants/card_ids.h` (generated from manifest) |
| Custom portraits / thought bubbles | `documentation/custom-portraits.md`, `documentation/thought-bubbles.md` |
| Status menu label/value layout | `documentation/status-menu-layout.md` → `src_custom/status_menu_hooks.c` |
| LynJump contract | `documentation/lynjump-replacements.md`, `tools/validate_lynjump.py` |
| Tests and CI locally | `documentation/tdd-framework.md`, `make test-host` |
| Recent agent context | **[SESSION_LOG.md](SESSION_LOG.md)** |

---

## Core systems

### Custom cards

1. Entry in `tools/card_data_manifest.json`
2. Generators produce `card_ids.h`, trunk tables, art includes, `card_data_hooks.c`
3. Art in `src_custom/assets/cards/` (80×80 and 24×24)
4. Effect hook in appropriate `src_custom/*_effects/` folder if needed
5. Validate: `make test-cards` or `make test-cards-build` if hooks link

### LynJump hooks

1. Vanilla function stays in `src/`
2. Replacement: `FunctionName__Replacement` in `src_custom/*_hooks.c`
3. Patch entry: `POIN FunctionName__Replacement` in `src_custom/LynJump.event`
4. Post-link: `apply_lynjump.py` patches the `.gba`

### Duel stat pipelines (important)

Two paths affect ATK/DEF display:

| Path | Used for | Key code |
|------|----------|----------|
| Field / info bar | Monster tiles, card info bar | `ApplyFieldZoneStatsToCardInfo` in `card_hooks.c` |
| Battle | Attack setup, damage calc | `SetAttackAction` → `SetFinalStat` in `code_803F02C.c` / `card_hooks.c` |

They must stay consistent. `GetFinalStage` sets global `gSetFinalStatZone` for paired `SetFinalStat` calls — field refresh must not leave it poisoned. `RefreshPendingBattleActionStatsFromZones` re-syncs battle stats from the field path before combat UI.

### Duel helpers API

Prefer `duel_helpers` over duplicating vanilla LP/draw/destroy flows:

- `Duel_ChangeLp`, `Duel_DrawCards`, `Duel_DestroyZone`, `Duel_ShowEffectTextTyped`
- `Duel_IncrementPermStageOnDuelistMonsters`, `Duel_RefreshMonsterStatOverlays`

Example: `src_custom/activated_effects/hourglass_of_life.c`.

---

## Build and test

| Command | When |
|---------|------|
| `make` / `make all` | Full ROM |
| `make test-host` | Fast daily loop (no ROM) |
| `make test-cards` | Manifest + card RAM layout |
| `make test-cards-build` | Card tests + full ROM link |
| `make test` | Host tests + ROM + ELF validators |
| `make add-card CARD='Name'` | Scaffold new manifest entry |

Requires `baserom.gba` in repo root and `tools/agbcc` installed.

---

## Agent workflow

1. **Read [SESSION_LOG.md](SESSION_LOG.md)** — what was last worked on, open threads.
2. **Skim this file** — confirm you are in the right layer (`src/` vs `src_custom/`).
3. **Use `.agents/skills/`** when the task matches a skill (add card, LynJump, validate-before-reply, …).
4. **Update SESSION_LOG.md** when finishing a meaningful chunk of work (see `.cursor/rules/session-context.mdc`).
