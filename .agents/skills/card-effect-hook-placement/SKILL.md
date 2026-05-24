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

- Spell effects:
  - `src/hooks/spell_effect_hooks.c`
  - `src/hooks/spell_effects/<card_name>.c`
- Trap effects:
  - `src/hooks/trap_effect_hooks.c`
  - `src/hooks/trap_effects/<card_name>.c`
- Activated monster effects:
  - `include/constants/monster_effects.h`
  - `src/hooks/monster_effect_hooks.c`
  - `src/hooks/activated_effects/<card_name>.c`
  - `tools/card_data_manifest.json`
- Permanent effects:
  - `src/hooks/permanent_effect_hooks.c`
  - `src/hooks/permanent_effects/<card_name>.c`
- Delayed cleanups or end-of-turn destruction:
  - `src/hooks/turn_effect_hooks.c`
- Search the matching dispatcher first, then the card-specific hook file, then the manifest or enum entry if the effect is activated. Avoid broad repo-wide searches unless the local files do not mention the card.

## Fast Path

1. Decide effect type: spell, trap, activated monster, permanent, or delayed cleanup.
2. Open the matching hook dispatcher listed above.
3. Open the card-specific hook file if it exists; otherwise create it.
4. For activated monster effects, update the enum, manifest, and dispatcher together.
5. For permanent effects, update the permanent hook and the card-specific file together.
6. Only then search `src/duel/*.c` if the hook surface is missing a needed entry point.

## Workflow

1. Identify the card and effect type.
2. Pick the matching hook directory.
3. Check the matching hook dispatcher first.
4. Create a single-purpose `.c` file for that card effect if one does not already exist.
5. Wire the hook file into the existing dispatcher or effect table.
6. Update `src/hooks/card_effect_tally.md` with the new effect entry and total count.
7. For activated monster effects, add or reuse a `MONSTER_EFFECT_*` entry in `include/constants/monster_effects.h`, then use that symbolic value in `tools/card_data_manifest.json` and route it through `src/hooks/monster_effect_hooks.c`.
8. For permanent effects, wire the card through `src/hooks/permanent_effect_hooks.c` and the matching file in `src/hooks/permanent_effects`.
9. Keep any vanilla edits limited to the smallest possible call site or registry entry.

## Notes

- Prefer one file per card effect.
- If the effect already has a hook-side home, extend that file instead of adding new vanilla logic.
- If the effect needs a replacement of a vanilla entrypoint, use the vanilla-function-replacements skill in addition to this one.
- Keep `src/hooks/card_effect_tally.md` current whenever hook-side card logic is added or moved.
- For activated monster effects, keep the manifest aligned with the enum: the card's `monsterEffect` field should name the enum constant, not hardcode a stray numeric value.
