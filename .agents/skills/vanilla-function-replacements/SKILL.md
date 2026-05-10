---
name: vanilla-function-replacements
description: "Use when editing vanilla functions in this repo. Apply behavior changes to the `__Replacement` function, not the vanilla function body. If no replacement exists, create one and wire it through a sibling `LynJump.event` per `documentation/lynjump-replacements.md`."
---

# Vanilla Function Replacements

When a request involves changing a vanilla function in this repo, make the change in the replacement function.

The vanilla function should stay intact unless the user explicitly asks to change the original symbol itself.

## Use This Skill When

- The user asks to edit an existing vanilla gameplay or engine function.
- The target function is part of the base linked game code and should be overridden safely.
- The requested behavior belongs in a LynJump replacement instead of the original entrypoint.

## Core Rule

- Apply behavior changes to `VanillaName__Replacement`.
- Do not rewrite the vanilla function body just to change runtime behavior.
- If no replacement exists yet, create one according to `documentation/lynjump-replacements.md`.

## Replacement Contract

For a vanilla function named `VanillaName`:

1. Leave `VanillaName` in place.
2. Add `LYN_REPLACE_CHECK(VanillaName);` above the replacement.
3. Create `void VanillaName__Replacement(...)` with the intended new behavior.
4. Add or update a sibling `LynJump.event` in the same directory.
5. Patch the vanilla ROM entry in `LynJump.event` and `POIN VanillaName__Replacement`.

## Authoring Workflow

1. Find the target vanilla function and inspect whether `VanillaName__Replacement` already exists nearby.
2. Check for a sibling `LynJump.event` in the same directory.
3. If the replacement exists, edit that replacement function.
4. If the replacement does not exist, copy the vanilla logic into a new `VanillaName__Replacement` and apply the requested change there.
5. Add `LYN_REPLACE_CHECK(VanillaName);` if missing.
6. Add or update the `LynJump.event` entry so the vanilla entrypoint jumps to the replacement symbol.
7. Validate the build contract when feasible.

## Event File Rules

- `LynJump.event` must sit beside the `.c` file.
- Use the existing narrow syntax used by this repo:
  - `PUSH`
  - `ORG $...`
  - `ALIGN 4`
  - `WORD ...`
  - `POIN SymbolName`
  - `POP`
- The `POIN` target should be the replacement symbol, not the vanilla symbol, unless the file already documents a different validated pattern.

## Constraints

- Never patch a function entry to jump to itself.
- `LYN_REPLACE_CHECK` is validation only. It does not redirect calls.
- The replacement must be a separate symbol from the vanilla entrypoint.
- Prefer keeping replacement logic self-contained.
- Preserve existing function signatures and calling conventions.

## Verification

When practical, run:

```bash
make
```

At minimum, ensure the source/event contract matches the repo rules described in `documentation/lynjump-replacements.md`.

## Example Pattern

```c
void VanillaName(void) {
  // original logic stays here
}

LYN_REPLACE_CHECK(VanillaName);
void VanillaName__Replacement(void) {
  // edited logic goes here
}
```
