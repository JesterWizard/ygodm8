---
name: Event CG Framework
overview: Add a custom DISPLAY_CG event command that shows a full-screen 240×160 indexed CG (240 BG colors, bank 0 reserved for font), fades in, runs a script "session" with vanilla textbox on top, then fades out and restores the overworld when text finishes or a session-ending opcode is reached.
todos:
  - id: cg-assets
    content: "Add CG asset pipeline: validate_cg.py, palette remap tool, Makefile rules, src_custom/assets/cgs/ layout"
    status: completed
  - id: cg-runtime
    content: "Implement cg_hooks.c: load 240×160 8bpp tiles, palette banks 1–15, hide map/OBJ, save/restore overworld display state"
    status: completed
  - id: cg-opcode
    content: Add DISPLAY_CG macro + vanilla_events.py encoding (0x7C '9') and script VM hook with fade-in blocking
    status: completed
  - id: cg-session
    content: "Implement session state machine: text-wait hooks, session-ending opcode detection, fade-out + restore, nested DISPLAY_CG replace"
    status: completed
  - id: cg-registration
    content: Add include/cg.h enum, cg_table.inc asset table, example CG asset + test script snippet
    status: completed
  - id: cg-docs-test
    content: Write documentation/event-cg.md and run make test
    status: completed
isProject: false
---

# Event CG Framework Plan

## Shared Requirements (Locked In)

| Decision | Choice |
|----------|--------|
| Colors | **240 BG colors** (palette banks 1–15); **bank 0 reserved** for vanilla dialogue font |
| Coverage | **Full 240×160**; hide map layers + OBJ (NPCs, portraits, bubbles) |
| Text | **Vanilla textbox** (BG0 + WIN1 dimming) on top of CG |
| Commands during CG | **Any opcode allowed** while CG is active; CG is a background swap, not a text-only mode |
| Close trigger | Auto-close when the **text session after DISPLAY_CG ends**; if **no TEXT** follows, **fade in then immediately fade out** before the next opcode |
| Nested CG | `DISPLAY_CG(B)` **replaces** active CG A (fade out A → fade in B) |
| Transitions | **Fade in, then text**; **fade out (blocking)** before the next post-session opcode |
| Authoring | **240×160 indexed PNG** under `src_custom/assets/cgs/` |
| IDs | **Named enum** in a header (e.g. `CG_INTRO_SCENE`) used as `DISPLAY_CG(CG_INTRO_SCENE)` |

## Architecture

```mermaid
sequenceDiagram
  participant Script as ScriptVM
  participant CG as cg_hooks.c
  participant Fade as FADE_SCREEN_logic
  participant Text as BG0_textbox

  Script->>CG: DISPLAY_CG(id)
  CG->>Fade: fade in (blocking)
  CG->>CG: load tiles/palette, hide map/OBJ
  alt TEXT follows
    Script->>Text: TEXT / PAGE_BREAK / CHOICE / ...
    Note over CG,Text: CG stays visible; PORTRAIT etc. OK
    Text->>Script: player finishes last text page
    Script->>CG: session end detected
  else no TEXT
    Script->>CG: next opcode reached
    Note over CG: skip text phase
  end
  CG->>Fade: fade out (blocking)
  CG->>CG: restore overworld VRAM/palette/DISPCNT
  Script->>Script: continue next opcode
```

### Why not reuse `SHOW_OVERWORLD_GRAPHIC`?

Vanilla [`sub_80512E0`](src/overworld/overworld_gfx_effects.c) **hides the textbox** (`sub_8053404`) and composes art from **OBJ sprites** with a separate palette region — opposite of “CG + dialogue on top.” The CG framework should follow the **alternate overworld background** pattern in [`CopyOverworldBgGraphics`](src/overworld/overworld.c) (full BG tileset + 240-color palette at `gPaletteBuffer + 16`) while keeping **BG0 text** alive.

### New event opcode

Vanilla `0x7C` subcommands `'0'`–`'8'` are all used ([`script.c`](src/overworld/script.c) lines 358–416). Add a **custom subcommand `'9'`**:

- Macro: `#define DISPLAY_CG(cg_id) COMMAND_7C_ARG(9, cg_id)` in [`events/scripts/event_macros.h`](events/scripts/event_macros.h)
- Parser: teach [`tools/vanilla_events.py`](tools/vanilla_events.py) to emit `[0x7C, ord('9'), id]` (same path as `COMMAND_7C_ARG`)
- Runtime: **LynJump hook** on `sub_80527E8` (or a targeted replacement adding `case '9'`) calling `DisplayCg__Hook(scriptCtx, id)` in new `src_custom/cg_hooks.c`

No new vanilla opcodes beyond an unused `'9'` slot — consistent with existing [`SCREEN_SHAKE`](events/scripts/event_macros.h) / `SHOW_OVERWORLD_GRAPHIC` patterns.

## Session Model (Text End Detection)

Define a **CG session** opened by `DISPLAY_CG` and closed before executing the first **session-ending** opcode.

**Session-compatible opcodes** (CG stays up):
- All text flow: `TEXT`, `LANGUAGE_TEXT`, `NEWLINE`, `PAGE_BREAK`, `CHOICE`, `PLAYER_NAME`, printable/script control chars
- Visual/dialogue helpers: `PORTRAIT`, `HIDE_PORTRAIT`, `REACTION`, `DELAY`, `FADE_SCREEN`, `SCREEN_SHAKE`
- Another `DISPLAY_CG` (replace flow)

**Session-ending opcodes** (trigger fade-out + restore, then run opcode):
- `DUEL`, `WARP`, `CUTSCENE`, `MOVE_OBJECT`, `SHOW_OBJECT`, `END`, `FALLTHROUGH`, music/map transitions, etc.

**Close timing with text:**
- After fade-in completes, script runs normally with CG visible.
- When the player finishes the **last text wait** (`unkC` returns to execute state) and the **next bytecode** is session-ending, run **blocking fade-out** before dispatching that opcode.
- If **no `TEXT` / language block** appeared in the session, fade out immediately after fade-in (still blocking) before the next opcode.

Track session state in **IWRAM globals** ([`asm/ram_map.s`](asm/ram_map.s) per [ram-map skill](documentation/ram-map.md)):
- `gCgActive`, `gCgSessionOpen`, `gCgId`, `gCgHadText`
- Snapshot buffer for restore: saved `REG_DISPCNT`, BG scroll/priority regs, relevant `gPaletteBuffer[0..255]`, map tilemap/tileset pointers or a “restore overworld gfx” flag

Hook **text-wait completion** (`sub_8052F60` / choice handler) and **script exit** ([`InitiateScript__Replacement`](src_custom/event_system_hooks.c) already calls `OverworldOverlay_RestoreDisplayRegs`) to guarantee cleanup if `END()` or an interrupt path fires mid-CG.

## Display / VRAM Strategy

**Target layout (Mode 0, matching overworld):**

| Layer | Role during CG |
|-------|------------------|
| BG1 or BG2 | Full-screen 240×160 **8bpp tiled** CG (600 tiles × 64 B = 38,400 B → ~2.4 charblocks; load into `gBgVram.cbb0` like RESHEF swap) |
| BG0 | Unchanged vanilla textbox path (`gVramBuffer + 0xD800`, font palette bank 0) |
| OBJ | Hidden (`REG_DISPCNT` clear OBJ enable or move OAM off-screen) |
| Other map BGs | Disabled or covered by CG tilemap |

**Palette:**
- Copy CG `.gbapal` (240 colors) → `gPaletteBuffer[16..255]` (480 bytes)
- Preserve / reload font palette → `gPaletteBuffer[0..15]` via existing `g82ADC8C` path in [`sub_804F5D8`](src/overworld/overworld.c)
- **Do not** clobber OBJ palettes unless needed; restore on session end via `sub_804F5D8()` + entity reload

**Fade in/out:**
- Reuse vanilla fade mechanics from [`sub_8053E34`](src/overworld/script_commands1.c) (`REG_BLDCNT`, `REG_BLDY`, `sub_804F218` wait loop) wrapped in CG-specific helpers so fade targets the CG layers without breaking textbox setup.

## Asset Pipeline

```
src_custom/assets/cgs/<name>.png   (240×160, indexed, ≤240 colors)
  → build/cgs/<name>.8bpp
  → build/cgs/<name>.gbapal       (480 bytes, banks 1–15)
  → build/cgs/<name>.lz
  → INCBIN in cg_hooks.c
```

**Authoring rules** (new `tools/validate_cg.py` + doc):
- Size exactly **240×160**
- Indexed PNG, **≤240** distinct non-transparent colors
- Palette index **0** = transparent in source (tool fills with opaque black or a designated backdrop color in 8bpp output for BG tiles)
- Build step **remaps** author indices `1..240` → hardware indices `16..255` (mirror of [`tools/offset_portrait_8bpp.py`](tools/offset_portrait_8bpp.py) but for BG bank layout)
- Makefile rules modeled on [`custom-portraits.md`](documentation/custom-portraits.md) portrait targets

**Registration:**
- Add `enum CutsceneGraphic` (or `enum EventCg`) in new [`include/cg.h`](include/cg.h)
- Table in `src_custom/cg_table.inc`: `{ enum id, tiles.lz, palette.gbapal, tilemap if precomputed }`
- First entry = `CG_NONE` guard; assign sequential IDs; scripts use enum names only

## Code Locations (New / Modified)

| File | Purpose |
|------|---------|
| [`include/cg.h`](include/cg.h) | `enum EventCg`, API declarations |
| [`src_custom/cg_hooks.c`](src_custom/cg_hooks.c) | Load/show/hide/restore; fade wrappers; session state machine |
| [`src_custom/cg_table.inc`](src_custom/cg_table.inc) | Asset table + `INCBIN` |
| [`src_custom/script_cg_hooks.c`](src_custom/script_cg_hooks.c) | `sub_80527E8` patch or `case '9'` handler; text-wait hooks |
| [`asm/ram_map.s`](asm/ram_map.s) | CG session globals + restore snapshot |
| [`src_custom/LynJump.event`](src_custom/LynJump.event) | Wire replacements |
| [`events/scripts/event_macros.h`](events/scripts/event_macros.h) | `DISPLAY_CG` macro |
| [`tools/vanilla_events.py`](tools/vanilla_events.py) | Emit `0x7C '9'` |
| [`tools/validate_cg.py`](tools/validate_cg.py) | PNG validation |
| [`Makefile`](Makefile) | CG asset build rules; hook object deps |
| [`documentation/event-cg.md`](documentation/event-cg.md) | Authoring guide (FogStages-style) |

## Example Script Usage

```c
DISPLAY_CG(CG_MEETING_YUGI)
TEXT("Hello world")
// CG auto-closes (fade out) before DUEL runs
DUEL(DUELIST_JOEY)
```

```c
DISPLAY_CG(CG_FLASHBACK)
TEXT("I remember...")
PAGE_BREAK()
PORTRAIT(PORTRAIT_JOEY, EXPRESSION_NEUTRAL, PORTRAIT_LEFT)
TEXT("That day changed everything.")
HIDE_PORTRAIT()
// CG closes after final TEXT page
WARP(LOCATION_DOMINO, 0, 0, 0)
```

```c
DISPLAY_CG(CG_BRIEF_STING)
MOVE_OBJECT(OBJ_NPC, DIR_SOUTH, 0, FALSE)
// No TEXT → fade in, then immediate fade out, then MOVE_OBJECT
```

## Validation / Testing

1. `make test-host` — CG PNG validator + event macro compile
2. `make test` — full ROM build
3. Manual: one CG with single TEXT, multi-page TEXT + PORTRAIT, no-TEXT path, back-to-back `DISPLAY_CG` replace, script `END()` mid-CG cleanup

## Risks and Open Defaults

- **BG opacity:** GBA BG pixels are opaque; “transparent” index 0 in PNG is an authoring convenience — converted to a visible color in tiles. Full-screen CG avoids holes.
- **VRAM pressure:** 38 KB tile data fits, but charblock placement must not stomp BG0 text VRAM; follow RESHEF load addresses in `gBgVram.cbb0`.
- **Fade-out blocking:** Assumed **blocking** (next opcode waits for fade-out). Say if you want overlap later.
- **OBJ palette during CG:** NPC OBJ hidden; portrait OBJ may still render if `PORTRAIT` used — confirm visually that portrait palette bank 12 does not clash with CG BG palette (separate OBJ PLTT region, should be fine).
