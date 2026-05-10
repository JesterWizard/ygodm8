---
name: vanilla-function-replacements
description: "Use when editing vanilla functions in this repo. Keep vanilla source files clean, put all replacement functions in `src/hooks/*_hooks.c`, and wire them through `src/hooks/LynJump.event` per `documentation/lynjump-replacements.md`."
---

# Vanilla Function Replacements

When a request involves changing a vanilla function in this repo, make the change in a hook-side replacement function under `src/hooks`.

The vanilla function should stay intact unless the user explicitly asks to change the original symbol itself.

## Use This Skill When

- The user asks to edit an existing vanilla gameplay or engine function.
- The target function is part of the base linked game code and should be overridden safely.
- The requested behavior belongs in a LynJump replacement instead of the original entrypoint.

## Core Rule

- Apply behavior changes to `VanillaName__Replacement`.
- Do not rewrite the vanilla function body just to change runtime behavior.
- Do not place replacement functions in the original source directory.
- If no replacement exists yet, create one according to `documentation/lynjump-replacements.md`.

## Replacement Contract

For a vanilla function named `VanillaName`:

1. Leave `VanillaName` in place.
2. Create a duplicate hook-side file in `src/hooks` named after the source file with `_hooks` appended, for example `src/hooks/overworld_hooks.c`.
3. Add `LYN_REPLACE_CHECK(VanillaName);` above the replacement in that hook-side file.
4. Create `void VanillaName__Replacement(...)` with the intended new behavior.
5. Add or update `src/hooks/LynJump.event`.
6. Patch the vanilla ROM entry in `src/hooks/LynJump.event` and `POIN VanillaName__Replacement`.

## Authoring Workflow

1. Find the target vanilla function and identify its source file.
2. Look for the corresponding hook-side file in `src/hooks` named `<source>_hooks.c`.
3. Edit the replacement there if it already exists.
4. If it does not exist, create the hook-side file and copy only the logic needed for `VanillaName__Replacement`.
5. Add `LYN_REPLACE_CHECK(VanillaName);` if missing.
6. Add or update the entry in `src/hooks/LynJump.event` so the vanilla entrypoint jumps to the replacement symbol.
7. Validate the build contract when feasible.

## Event File Rules

- Use `src/hooks/LynJump.event` for hook entries.
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
LYN_REPLACE_CHECK(VanillaName);
void VanillaName__Replacement(void) {
  // edited logic goes here
}
```
