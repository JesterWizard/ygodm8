# LynJump Replacements

This repo supports replacing selected vanilla functions by:

1. keeping the original linked function in place
2. compiling a separate replacement symbol into appended ROM space
3. patching the vanilla entrypoint with a jump stub from a sibling `LynJump.event`

`LYN_REPLACEMENT` marks a replacement for validation and places it in appended ROM space. It does not redirect anything by itself.

## Current Example

Current example files:

- [src/duel/life_points.c](/home/username/Github/ygodm8/src/duel/life_points.c:1)
- [src/duel/LynJump.event](/home/username/Github/ygodm8/src/duel/LynJump.event:1)
- [tools/validate_lynjump.py](/home/username/Github/ygodm8/tools/validate_lynjump.py:1)
- [tools/apply_lynjump.py](/home/username/Github/ygodm8/tools/apply_lynjump.py:1)

The vanilla function stays as:

```c
void CapLifePointsAfterDuel(void) {
  gLifePointsOutsideDuel = gDuelLifePoints[DUEL_PLAYER];

  if (gLifePointsOutsideDuel > 8000)
    gLifePointsOutsideDuel = 8000;
}
```

The replacement is emitted under a different symbol:

```c
LYN_REPLACEMENT(CapLifePointsAfterDuel) void CapLifePointsAfterDuel__Replacement(void) {
  gLifePointsOutsideDuel = gDuelLifePoints[DUEL_PLAYER];

  if (gRuntimeConfig.restore_life_points_after_duel == TRUE)
    gLifePointsOutsideDuel = 8000;

  if (gLifePointsOutsideDuel > 8000)
    gLifePointsOutsideDuel = 8000;
}
```

The corresponding installer file patches the original entry:

```event
PUSH
ORG $48CEC
ALIGN 4
WORD $46C04778 $E59FC000 $E12FFF1C
POIN CapLifePointsAfterDuel__Replacement
POP
```

## Authoring Rules

When adding a new replacement:

1. Leave the original vanilla function intact.
2. Prefix the replacement function with `LYN_REPLACEMENT(VanillaName)`.
3. Name the replacement `VanillaName__Replacement`.
4. Put a sibling `LynJump.event` in the same directory as the source file.
5. In `LynJump.event`, patch the vanilla ROM offset and `POIN` the replacement symbol.

The current validator maps `Name__Replacement` back to `Name` when checking the marker embedded by `LYN_REPLACEMENT`.

## Build Flow

Normal build:

```bash
make
```

What happens:

1. `ygodm8.elf` is linked.
2. `python3 tools/validate_lynjump.py` checks the source/event contract.
3. `ygodm8.gba` is produced from the ELF.
4. `python3 tools/apply_lynjump.py ygodm8.elf ygodm8.gba` writes jump stubs into the ROM.

`LynJump.event` files are build inputs. Changing one causes the ROM target to rebuild and be repatched.

## Validation Contract

`tools/validate_lynjump.py` enforces two directions:

Source to event:

- every `LYN_REPLACEMENT(Name)` requires a sibling `LynJump.event`
- that event file must reference either `Name` or `Name__Replacement`

Event to source:

- every `POIN Symbol` in a `LynJump.event` must have a matching sibling `.c`
- if the symbol ends in `__Replacement`, the validator expects `LYN_REPLACEMENT(BaseName)`

## Patcher Details

`tools/apply_lynjump.py` supports the narrow syntax currently used here:

- `PUSH`
- `POP`
- `ORG $...`
- `ALIGN 4`
- `WORD ...`
- `POIN SymbolName`

Function symbols are written with the Thumb bit set automatically.

This matters for replacements like:

- `CapLifePointsAfterDuel__Replacement` linked at `0x09000008`
- patched pointer written as `0x09000009`

Without the Thumb bit, the game will crash when the jump runs.

## Important Constraints

- Do not patch a function entry to jump to itself. That creates an infinite loop.
- `LYN_REPLACEMENT` does not perform any runtime dispatch.
- The jump target must be a separate symbol from the vanilla entrypoint.
- Replacement code can safely read normal global symbols and config data, but cross-region calls may require extra care.
- If possible, keep replacement logic self-contained to reduce veneer/interworking risk.
