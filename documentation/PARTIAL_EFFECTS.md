# Partial Effects Backlog

Auto-generated living list of effect files with `ponytail:` or `Ceiling:` notes (implemented, but missing hooks / engine pieces).
Find follow-up work here — stubs live in `STUB_EFFECTS.md`.
Rows vanish when all `ponytail:` / `Ceiling:` comments are removed from the file.
Missing-surface tags: [`PARTIAL_EFFECTS_TAXONOMY.md`](PARTIAL_EFFECTS_TAXONOMY.md). Engine migration: [`effect-data-system.md`](effect-data-system.md).

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials + taxonomy
```

**Last updated:** 2026-09-03 23:19 UTC  
**Remaining partials:** `2`

## Counts by kind

| Kind | Count |
|------|------:|
| `activated` | 2 |
| **total** | **2** |

## activated (2)

### `HARPIE_CONDUCTOR`
- path: `src_custom/activated_effects/harpie_conductor.c`
- L210: Damage Step not detected — may fire on battle-return paths.

### `HARPIE_HARPIST`
- path: `src_custom/activated_effects/harpie_harpist.c`
- L13: EffectOpt is one flag per cardId — EP search uses a separate turn OPT.
