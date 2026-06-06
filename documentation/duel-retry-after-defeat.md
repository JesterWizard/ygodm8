# Duel Retry After Defeat

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Vanilla duels always end after a loss: loss text plays, the screen fades out, and overworld script logic decides whether you stay on the map or return home (`return_home_after_defeat`). There is no way to immediately replay the same opponent without walking away and starting the duel again.

This feature adds an optional **Retry duel?** prompt at the end of a lost ingame duel. When enabled, the player can choose **Yes** to restart the duel in place (new random draw, fresh board and hands) or **No** to accept defeat and follow the normal post-loss flow.

The feature is controlled by `gRuntimeConfig.offer_duel_retry_after_defeat` in `configs/runtime.c` (default **off**). When disabled, `DuelMain__Replacement` delegates the loss path to vanilla `HandleOutcome` / `FinishDuel` behavior unchanged.

## Plan

### Runtime toggles

| Toggle | Default | Effect |
|--------|---------|--------|
| `offer_duel_retry_after_defeat` | `FALSE` | Shows the retry prompt after a player loss |
| `return_home_after_defeat` | `TRUE` | Still applies when the player finally accepts defeat (chooses **No** or wins after one or more retries) |

These toggles are independent. Retry only changes what happens **before** the duel fully ends; once the player declines a retry, overworld defeat handling is unchanged.

### Player-facing prompt

English-only text in the duel textbox:

```
Retry duel?
  Yes
  No
```

Options are indented two spaces so the `>` cursor (column 0) does not overlap the label text. **Up** / **Left** and **Down** / **Right** move between **Yes** and **No**. **A** confirms; **B** cancels and is treated as **No**.

### Loss flow (toggle on)

```
Duel ends (player lost)
├── ShowDuelLossMessages          // LP/deck-out + duel loss text (no penalties yet)
├── PromptDuelRetry               // Yes / No; textbox stays visible during input
├── Yes
│   ├── FadeDuelToBlack           // single palette fade out
│   ├── AdvanceDuelRandomState    // LfsrNextWord()
│   ├── ResetIngameDuelForRetry   // decks, board, LP, first player
│   └── Resume turn loop          // skip second init to avoid display flash
└── No
    ├── ApplyDuelLossPenalties    // ante removal, CapLifePointsAfterDuel, etc.
    ├── FadeDuelToBlack
    └── Return to overworld       // return_home_after_defeat script branch
```

### What resets on **Yes**

`ResetIngameDuelForRetry` mirrors vanilla `InitIngameDuel`:

| State | Behavior |
|-------|----------|
| Life points | Restored via `InitDuelLifePoints` |
| Board | Cleared via `InitBoard` |
| Decks | Rebuilt and shuffled for both duelists |
| Hands | Empty after deck init (fresh opening draws) |
| First player | Random (`RandRangeU8(0, 1)`) |
| RNG stream | Advanced once (`LfsrNextWord`) before shuffle / turn order |
| Ante / LP cap | **Not** applied until the player finally accepts defeat |

### Transition notes

- **First duel entry** still uses vanilla `MosaicEffect()` once at loop start.
- **Retry** uses one `FadeDuelToBlack()` only; `MosaicEffect()` is **not** called again (it would double-fade).
- After a successful retry, `skipInit` prevents `ResetIngameDuelForRetry` from running twice at the loop head (the second call would flash black via `sub_8041090` → `REG_DISPCNT = 0` / `DisableDisplay()`).
- The prompt keeps the textbox window active by calling `RestoreDuelPromptTextboxDisplay` each frame and using `RunTextRenderTask` without `UpdateDuelGfxExceptField` (which clears `WIN1`).

### Win path

If the player wins (including after any number of retries), `FinishDuel(FALSE)` runs `HandleOutcome` → `HandleWin` and fades out once. No retry prompt is shown.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Runtime toggle | `offer_duel_retry_after_defeat` in `configs/runtime.h` and `configs/runtime.c` | Master on/off for the retry prompt |
| Duel entry / retry loop | `DuelMain__Replacement` in `src_custom/duel_main_hooks.c` | Replaces vanilla `DuelMain`; owns mosaic, init skip, and retry loop |
| Loss messages (no penalty) | `ShowDuelLossMessages` in `src_custom/duel_main_hooks.c` | Displays defeat text before the retry choice |
| Yes / No prompt | `PromptDuelRetry`, `ShowDuelRetryPromptText` in `src_custom/duel_main_hooks.c` | Textbox render, cursor highlight, input loop |
| Prompt string | `sText_DuelRetryPrompt` in `src_custom/duel_main_hooks.c` | `"Retry duel?#0  Yes#0  No"` |
| Duel reset | `ResetIngameDuelForRetry` in `src_custom/duel_main_hooks.c` | Full ingame duel state rebuild |
| RNG advance | `AdvanceDuelRandomState` in `src_custom/duel_main_hooks.c` | Calls `LfsrNextWord` before reshuffle |
| Fade out | `FadeDuelToBlack` in `src_custom/duel_main_hooks.c` | Palette fade used on retry and duel end |
| Final loss penalties | `ApplyDuelLossPenalties` in `src_custom/duel_main_hooks.c` | Ante, LP cap, card-shop duel cleanup |
| Duel end helper | `FinishDuel` in `src_custom/duel_main_hooks.c` | Win path, declined-retry path, vanilla loss path |
| LynJump wiring | `POIN DuelMain__Replacement` at `$21718` in `src_custom/LynJump.event` | Replaces vanilla `DuelMain` |
| Vanilla reference | `DuelMain`, `InitIngameDuel`, `DuelEnd` in `src/duel/duel_main.c` | Original turn loop and end-of-duel fade |
| Post-defeat overworld | `InitiateRegularDuelScript` in `src_custom/code_8051958_hooks.c` | `return_home_after_defeat` loss script branches |
| Textbox flush | `sub_8041014` in `src/duel/duel_textbox.c` | Copies prompt tiles to BG VRAM each frame |

## TODO

- Add a short clip or screenshot of the retry prompt in this doc.
- Consider localized prompt strings if non-English builds are needed later.

## Limitations & Bugs

- Only applies to **ingame** duels entered through `DuelMain` (overworld script `0x40 '0'`). Link duels and other duel types are unchanged.
- Surrender and other forfeit paths that declare the player defeated will also offer a retry when the toggle is on.
- Loss penalties (ante card removal, `CapLifePointsAfterDuel`) are deferred until the player chooses **No** or exhausts retries by losing without choosing **Yes** again. Intermediate losses on **Yes** do not consume ante or update overworld LP.
- The prompt is **English only**; other languages fall through to the same string until translations are added.
- `return_home_after_defeat` is not bypassed by retrying: it only affects the overworld script after the duel fully ends with a player loss.
- Retry does not re-run `DuelTrunkMenu` or ante selection; the same ante and deck choices from duel start remain in effect.
