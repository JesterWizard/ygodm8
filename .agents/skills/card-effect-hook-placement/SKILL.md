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

## Workflow

1. Identify the card and effect type.
2. Pick the matching hook directory.
3. Create a single-purpose `.c` file for that card effect if one does not already exist.
4. Wire the hook file into the existing dispatcher or effect table.
5. Keep any vanilla edits limited to the smallest possible call site or registry entry.

## Notes

- Prefer one file per card effect.
- If the effect already has a hook-side home, extend that file instead of adding new vanilla logic.
- If the effect needs a replacement of a vanilla entrypoint, use the vanilla-function-replacements skill in addition to this one.
