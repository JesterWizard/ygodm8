# Partial Effects Taxonomy

Auto-generated companion to [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md).
Each `ponytail:` / `Ceiling:` note is tagged with its **primary missing engine surface** so Phase work in [`effect-data-system.md`](effect-data-system.md) can target events/ops that unblock many cards at once.

```bash
python3 tools/stub_effect_queue.py --write-list
```

**Last updated:** 2026-09-03 23:19 UTC  
**Ceiling lines tagged:** `2`  
**Partial files:** `2`

## Counts by missing surface

| Tag | Count | Suggested phase |
|-----|------:|-----------------|
| `event.OnBattleDestroy` | 1 | 3 |
| `op.Search` | 1 | 1 |
| **total** | **2** | |

Highest-ROI unblock for this backlog is usually **`event.OnStandby` (OPT)** plus destroy/summon/battle listeners (Phase 3), not per-card rewrites.

## `event.OnBattleDestroy` (1)

- `HARPIE_CONDUCTOR` (activated): L210: Damage Step not detected — may fire on battle-return paths.

## `op.Search` (1)

- `HARPIE_HARPIST` (activated): L13: EffectOpt is one flag per cardId — EP search uses a separate turn OPT.
