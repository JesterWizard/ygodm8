---
name: summon-popup-animations
overview: Add a framework for full-screen summon pop-up animations (Master Duel style) for specific cards, starting with Jinzo, by reusing the existing overworld GFX effects engine with display state save/restore during duel placement.
todos:
  - id: create-framework-file
    content: Create src_custom/summon_animations.c with config table, display save/restore, and TryPlaySummonAnimation dispatch function
    status: completed
  - id: create-header
    content: Create header declaring TryPlaySummonAnimation()
    status: completed
  - id: wire-human-placement
    content: Insert TryPlaySummonAnimation() call in sub_80449D8__Replacement (code_8043EF4_hooks.c)
    status: completed
  - id: wire-programmatic-placement
    content: Insert TryPlaySummonAnimation() call in PlaceMonsterFromId() (duel_helpers.c)
    status: completed
  - id: add-jinzo-config
    content: Add Jinzo entry to gSummonAnimConfigs[] with GRAPHIC_JINZO_FULL_ART and MUSIC_334
    status: completed
  - id: validate
    content: Run make test-cards-build and fix any compile/link errors
    status: completed
isProject: false
---

# Summon Pop-Up Animation Framework

## Goal
When a card with a registered summon animation hits the field (any placement: normal summon, special summon, flip, reborn, set, opponent's placement), blank the duel board, play a full-screen sprite animation with music, then restore the duel state and continue with activation text normally.

---

## Architecture

```
Placement hook (sub_80449D8 / PlaceMonsterFromId)
  └─ TryPlaySummonAnimation(cardId)          ← NEW: check and dispatch
       └─ if card has animation:
            ├─ SaveDuelDisplayState()         ← save BG/OAM/palette/VRAM
            ├─ REG_DISPCNT = 0                ← blank screen
            ├─ PlaySummonAnimation_ForCard(cardId)
            │    ├─ PlayMusic(animMusicId)
            │    ├─ Run overworld GFX effect  ← reuse sub_80512E0(NULL, graphicId)
            │    └─ ResumeDuelMusic()
            ├─ RestoreDuelDisplayState()      ← restore BG/OAM/palette/VRAM
            └─ RunDuelGfxUpdate()             ← redraw duel board
  └─ continue with normal placement flow
```

### Key design decisions:

- **Reuse, don't rebuild**: Call the existing `sub_80512E0` (overworld GFX effect dispatcher) with pre-existing Jinzo graphic IDs. The overworld system already handles full-screen sprite playback with frame sequencing, palette effects, and VBlank timing. No new rendering code.
- **Save/restore display state**: Since the GFX effects engine writes directly to OBJ VRAM, OAM, and palette memory, we must snapshot and restore the duel's display state around the animation call.
- **Framework is a lookup table**: New file `src_custom/summon_animations.c` with a `gSummonAnimConfigs[]` table mapping `card_id` → `{graphic_id, music_id}`. Adding a new card means adding one row to the table plus ensuring the art exists in ROM.
- **No hook changes needed for Jinzo**: Jinzo is vanilla. The animation framework lives in the placement hooks that already intercept all summons.

---

## Implementation Steps

### Step 1: Create animation framework file

New file: `src_custom/summon_animations.c`

- Define `struct SummonAnimConfig { u16 cardId; u8 graphicId; u16 musicId; }`
- Define `gSummonAnimConfigs[]` table (initially one entry: `{JINZO, GRAPHIC_JINZO_FULL_ART, MUSIC_334}`)
- Implement `TryPlaySummonAnimation(u16 cardId)` — looks up config, if found runs full animation cycle
- Implement `SaveDuelDisplayState()` / `RestoreDuelDisplayState()` — snapshot `REG_DISPCNT`, `BG*CNT`, full palette buffer, full OAM buffer, and the OBJ VRAM region used by the duel's card sprites
- Implement `ResumeDuelMusic()` — restores the duel music that was playing before the animation

### Step 2: Wire into both placement paths

**Human player path** (`src_custom/code_8043EF4_hooks.c` → `sub_80449D8__Replacement`):

Insert `TryPlaySummonAnimation()` at the very top of the placement function, after the validation gates but before any board state mutation. If animation runs (returns TRUE), the rest of the placement continues normally.

**Programmatic/AI path** (`src_custom/duel_helpers.c` → `PlaceMonsterFromId()`):

Insert the same `TryPlaySummonAnimation()` call before placement logic. The card ID is already known at that point.

### Step 3: Handle "either side of the board"

Both placement hooks already handle both player and opponent placements. No extra work needed — the `cardId` is available regardless of which duelist is summoning.

### Step 4: Add Jinzo config entry

Add `{JINZO, GRAPHIC_JINZO_FULL_ART, MUSIC_334}` to `gSummonAnimConfigs[]`. No new art or music needed — Jinzo already has a full-art overworld graphic (14) with downward-scroll animation frames in the vanilla ROM.

### Step 5: Validation

- `make test-cards-build` to confirm the framework compiles and links
- Manual test: Jinzo summoned in a runtime test hand should play the full animation with music, then show activation text, then the duel resumes normally
- Manual test: opponent summons Jinzo (e.g., via AI) — animation should still play

---

## Files to Create

| File | Purpose |
|------|---------|
| `src_custom/summon_animations.c` | Framework: config table, dispatch, display save/restore |

## Files to Modify

| File | Change |
|------|--------|
| `src_custom/code_8043EF4_hooks.c` | Call `TryPlaySummonAnimation()` in `sub_80449D8__Replacement` |
| `src_custom/duel_helpers.c` | Call `TryPlaySummonAnimation()` in `PlaceMonsterFromId()` |
| `src_custom/summon_animations.h` (or `include/`) | Header declaring `TryPlaySummonAnimation()` |

---

## Risks and Mitigations

- **Risk**: Display state save/restore is incomplete, leaving the duel board corrupted.  
  **Mitigation**: Save the full palette buffer (1KB), full OAM buffer (1KB), BG control registers, and the OBJ VRAM charblock that the duel uses for card sprites. The GFX effects engine only touches CBB5 (OBJ block 5). If the duel uses a different block, no VRAM backup is needed.

- **Risk**: Music state restoration fails, leaving wrong music after animation.  
  **Mitigation**: Store the current music track ID before calling `PlayMusic()`, then call `PlayMusic(originalId)` after the animation. The existing `PlayMusic` function tracks the currently playing track.

- **Risk**: The `ScriptCtx*` parameter required by `sub_80512E0` causes issues.  
  **Mitigation**: Check if passing NULL is safe for the horizontal-slide renderer (`sub_804FE78`). If not, create a dummy `ScriptCtx` on the stack. The renderer code path for graphic type 3 doesn't dereference the script pointer.

- **Risk**: The animation delays gameplay more than expected. Jinzo's full-art animation has ~38 scroll steps at 2 VBlanks each (~1.3 seconds) plus an 80-frame hold (~1.3 seconds), totaling ~2.6 seconds. This is acceptable but should be confirmed.