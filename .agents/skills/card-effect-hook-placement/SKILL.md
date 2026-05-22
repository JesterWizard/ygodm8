---
name: card-effect-hook-placement
description: "Use when adding or moving a card-specific effect in this repo; place the effect body in a dedicated hook file under `src/hooks/spell_effects`, `src/hooks/trap_effects`, `src/hooks/activated_effects`, or `src/hooks/permanent_effects` instead of editing vanilla gameplay source."
---

# Card Effect Hook Placement

Use this skill when creating or moving a card-specific effect.

## Core Rule

- Do not put new card-effect bodies in vanilla `src/duel/*.c` files.
- Put each effect in its own hook-side file under the matching category:
  - `src/hooks/spell_effects`
  - `src/hooks/trap_effects`
  - `src/hooks/activated_effects`
  - `src/hooks/permanent_effects`
- Keep vanilla files as dispatch or registration only when they must remain in the build path.

## Where To Look First

- `src/hooks/spell_effect_hooks.c` for spell-card effects.
- `src/hooks/trap_effect_hooks.c` for trap-card effects.
- `src/hooks/monster_effect_hooks.c` for monster activation effects.
- `src/hooks/turn_effect_hooks.c` for graveyard and other turn-scan effects.
- `src/hooks/permanent_effect_hooks.c` for continuous effects.
- Search the matching dispatcher for the card name or `gCardInfo`/`gActiveEffect` checks before looking at vanilla code.

## Workflow

1. Identify the card and effect type.
2. Pick the matching hook directory.
3. Check the matching hook dispatcher first.
4. Create a single-purpose `.c` file for that card effect if one does not already exist.
5. Wire the hook file into the existing dispatcher or effect table.
6. Update `src/hooks/card_effect_tally.md` with the new effect entry and total count.
7. Keep any vanilla edits limited to the smallest possible call site or registry entry.

## Notes

- Prefer one file per card effect.
- If the effect already has a hook-side home, extend that file instead of adding new vanilla logic.
- If the effect needs a replacement of a vanilla entrypoint, use the vanilla-function-replacements skill in addition to this one.
- Keep `src/hooks/card_effect_tally.md` current whenever hook-side card logic is added or moved.
