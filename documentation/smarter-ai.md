# Smarter Dueling AI

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Vanilla opponent AI simulates hundreds of candidate actions each turn, assigns each one a priority score, and always executes the single highest-scoring line. That makes duels predictable: the same board state tends to produce the same sequence of plays.

Smarter AI keeps the vanilla simulation engine but adds a uniform tactical modifier pipeline before action selection. When `enable_smarter_ai` is on in [`configs/runtime.c`](../configs/runtime.c), the AI varies among near-optimal lines with human-like board awareness instead of repeating one fixed script.

For the sim budget / prune → score → beam target architecture (orthogonal to this picker), see [`fast-ai-architecture.md`](fast-ai-architecture.md).

## Plan

Decision flow:

1. Vanilla AI simulates all candidate actions and fills the priority table.
2. `AiDecision_PickAction` builds context (LP, turn count, board scan).
3. Modifier chain adjusts priorities with small capped deltas.
4. The picker chooses the highest-priority candidate in the top band (ties broken at random).
5. If a lethal line exists, only lethal candidates are considered.
6. Summons and spell/trap sets must target the same preferred empty on-screen zone (player: left; mirrored opponent: right).
7. Else if a winning face-up attack exists (and backrow probing is not pending), only those attacks are considered.
8. After execution, duel memory records the chosen action and updates board knowledge.

| Module | Behavior |
|--------|----------|
| Variance picker | Highest priority within `0x15000` of the best score; random tie-break only |
| LP mood | Boost aggression when behind; caution when ahead |
| Setup bias | Early turns prefer set spell/trap/defense over naked commits |
| Duel memory | Down-rank repeating the previous turn's exact line |
| Attack targeting | Prefer beatable face-up targets over unknown face-down ones; favor remembered flipped monsters |
| Attack order | Probe with weaker attackers when player has set backrow; vary order afterward |
| Tribute board | Favor tribute when the summon has type advantage over at least one face-up threat, even if it loses to another; avoid tributes that worsen the whole board |
| Hand read | When the opponent's hand is visible, nudge setup or pressure based on likely threats |
| Zone placement | Monsters and spell/trap sets share `Board_PreferredEmptyFixedCol`: player rows fill left-to-right; mirrored opponent rows fill right-to-left |
| Destroy face-up | When a winning face-up attack is competitive (and trap probing is not pending), only those attacks are considered |
| Summon quality | Prefer stronger monsters for the preferred monster zone |
| Wasteful lines | Down-rank discards when summoning or removing a face-up monster is clearly available |

All duelists share the same tactical rules. There is no per-duelist personality tuning in the runtime path.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Runtime toggle | `enable_smarter_ai` in [`configs/runtime.h`](configs/runtime.h) and [`configs/runtime.c`](configs/runtime.c) | Master on/off for smarter AI |
| LynJump entry | `sub_800EF0C__Replacement` in [`src_custom/ai_hooks.c`](src_custom/ai_hooks.c) | Redirects action selection to the framework |
| Core pipeline | `AiDecision_PickAction` in [`src_custom/ai_decision/ai_decision_core.c`](src_custom/ai_decision/ai_decision_core.c) | Builds context, runs modifiers, selects action |
| Modifiers | [`src_custom/ai_decision/ai_modifiers.c`](src_custom/ai_decision/ai_modifiers.c) | LP mood, setup, memory, attack/tribute/hand tactics |
| Board scan | [`src_custom/ai_decision/ai_tactics.c`](src_custom/ai_decision/ai_tactics.c) | Pre-decision board and visible-hand analysis |
| Board placement | [`src_custom/board_placement.c`](src_custom/board_placement.c), [`include/board_placement.h`](include/board_placement.h) | Leftmost empty zone on screen (fixed-row scan) |
| Player set placement | `sub_80442AC__Replacement`, `sub_80449D8__Replacement` in [`src_custom/code_8043EF4_hooks.c`](src_custom/code_8043EF4_hooks.c) | Human player spell/trap sets snap to leftmost backrow slot |
| Action decode | [`src_custom/ai_decision/ai_action_decode.c`](src_custom/ai_decision/ai_action_decode.c) | Maps action indices to categories, zones, and card ids |
| Duel memory | `gAiDuelMemory` in [`asm/ram_map.s`](asm/ram_map.s), [`src_custom/ai_decision/ai_memory.c`](src_custom/ai_decision/ai_memory.c) | Repeat avoidance, flip memory, attack order |
| Execute hook | `sub_800E0D4__Replacement` in [`src_custom/ai_tribute_hooks.c`](src_custom/ai_tribute_hooks.c) | Tempo delay + memory record |
| Duel reset | `InitDuelDeck__Replacement` in [`src_custom/duel_util_hooks.c`](src_custom/duel_util_hooks.c) | Clears memory at duel start |
| Action table gen | [`tools/generate_ai_action_table.py`](tools/generate_ai_action_table.py) | Extracts `gAED58[]` from vanilla `ai.c` |

## TODO

- Playtest tribute-board heuristics against multi-monster fields.
- Optional debug overlay showing top candidate priorities during AI turns.

## Limitations & Bugs

- Modifier deltas are intentionally small so AI stays competent; destroy-face-up still requires a competitive line within `0x25000` of vanilla's global best.
- Preferred zone placement is always enforced on every candidate (lethal excepted). Monsters and spell/trap sets use the same mirror-aware scan in `board_placement.c`.
- Human player hand → field placement uses the same rules when smarter AI is enabled.
- Hard filters defer face-up removal while set backrow is unprobed (first attack of the turn).
- Attribute matchup checks respect `disable_element_system` in runtime config.
- Visible-hand reads use vanilla `CanOpponentSeeCard`; most hand cards are hidden unless an effect exposes them.
- Tribute-board scoring compares summon matchup to current field matchup but cannot predict which exact monsters vanilla will tribute.
- Leftmost-summon forcing applies to normal and tribute summons from hand; ritual lines use separate zone encoding and are not forced by this rule.
- Leftmost-set forcing applies to normal, equip, ritual, and trap sets from hand into the spell/trap backrow.
- Destroy-face-up forcing covers winning attacks on face-up monsters; spell/trap removal lines are not detected yet.
- Rebuild after editing `src/duel/ai.c` action templates so the generated action table stays in sync.

Please report unexpected AI loops or obviously bad lines with the duelist, turn, and board state.
