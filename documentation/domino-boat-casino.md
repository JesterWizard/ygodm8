# Domino Boat Casino

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

The Domino Pier left-room NPCs (map 25) run two stake mini-games instead of flavor-only dialogue:

| NPC | Game |
|-----|------|
| Ship dealer | Blackjack (monster levels 1–11; 11 = Ace) |
| Casino patron | Concentration (4×5 memory match) |

Stakes are Domino **100** / **1000**, or any trunk ante card. Money wins pay 1:1 (stake deducted up front; win returns `2 × bet`). Ante wins draw from a prize pool (`IsNormalAnte` selects primary vs secondary). Ties / pushes refund money or keep the ante.

## Plan

1. Talk to the NPC:
   - Dealer **A** → Blackjack offer → `SPECIAL(36)`.
   - Patron **A** → Concentration rules yes/no; **Yes** explains the game.
   - Patron **R** → not a duelist, challenge yes/no; **Yes** → mosaic fade → `SPECIAL(37)`.
2. C stake menu (Domino amounts or trunk ante picker).
3. Play the mini-game overlay (start-menu BG + mini-card OAM).
4. Resolve payout → overworld restore.

Blackjack is minimal: hit/stand, dealer stands on all 17s, infinite shoe of real monsters by level, push on tie. Concentration alternates turns (no extra turn on match); fair-ish NPC remembers seen cards; clear board then compare match counts.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Public entry | `include/casino.h` | `Casino_BlackjackMain`, `Casino_ConcentrationMain`, hand-total helper |
| Shared stakes / UI | `src_custom/casino/casino_common.c` | Stake prompt, payout, mini-card helpers |
| Prize stubs | `src_custom/casino/casino_prizes.c` | Primary / secondary card ID tables |
| Blackjack | `src_custom/casino/casino_blackjack.c` | Deal / hit / stand loop |
| Concentration | `src_custom/casino/casino_concentration.c` | 4×5 board, memory AI |
| SPECIAL dispatch | `sub_8054AB0__Replacement` in `src_custom/script_commands2_hooks.c` | Cases 36 / 37 |
| Map scripts | `events/scripts/map_25_state_{01,02,03}.c` | Dealer A = Blackjack; patron A = rules, R = Concentration |

| SPECIAL names | `tools/vanilla_events.py` `SPECIAL_COMMANDS` | `casino_blackjack`, `casino_concentration` |

## TODO

- Fill prize pools with balanced drops.
- Richer Blackjack card display (more than two face-up VRAM slots).
- Optional runtime toggle to disable casino SPECIALs.

## Limitations & Bugs

- Blackjack only keeps two face-up mini-art slots in OBJ VRAM; other cards show as backs while totals remain correct.
- Concentration cursor reuses the start-menu cursor OBJ over the selected cell.
- State 02 no longer uses the scared-dealer flag gate on talk (Blackjack offer replaces it); flag scripts remain in the file for address coverage.
- Play field forces a full-screen WIN0 so mini cards are not clipped by the stake-menu panel.
