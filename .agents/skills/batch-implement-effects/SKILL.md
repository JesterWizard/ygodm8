---
name: batch-implement-effects
description: "Use when implementing multiple card effect stubs, clearing the effect backlog, or when the user asks to speed up / batch card effects. Default is a multi-card work pack — never one card per session unless the user names a single card."
---

# Batch Implement Effects

## Default

**Do not implement one stub per session.** Take a pack of **8–12 cards** (spells preferred — no shared enum conflicts), implement all, run **one** `make` at the end.

## Start every batch

```bash
# Preferred: spells only, 12 cards, 3 parallel worker packs
python3 tools/stub_effect_queue.py --work-pack 12 --kind spell --workers 3

# Or template-scaffold a whole pattern (then tighten predicates):
python3 tools/stub_effect_queue.py --fill-all --pattern burn --dry-run
python3 tools/stub_effect_queue.py --fill-all --pattern draw_n --limit 6
```

Work packs land in `documentation/effect_work_packs/YYYY-MM-DD/` (`index.json`, `pack_NN.md`).

## Parallel agents

1. Generate `--work-pack N --workers K --kind spell`.
2. Launch **K** agents; give each agent **only** its `pack_NN.md` / `.json`.
3. Each agent edits **only** the listed effect `.c` files (spells = safe).
4. Parent runs **one** `make` after all workers finish.
5. Do **not** parallelize activated/permanent packs that touch `monster_effects.h` or shared hook tables — serialize those.

## Per card (inside a pack)

1. Read `effect_text` from the pack entry (or manifest).
2. Open `clone_path` if present; copy structure, swap IDs/filters/amounts.
3. If `pattern` is set and the text truly matches, `--fill` then tighten — do not blind-fill multi-step cards.
4. Replace every `TODO`. Use `duel_helpers.h`.
5. Continuous ATK/DEF field overlays: `Duel_FindBackrowCard*` / `Duel_IsBackrowCardOnField`, field check **before** name/`SetCardInfo` — see `.cursor/rules/stat-overlay-perf.mdc`.
6. Skip Timed Duel / runtime hand setup unless the card needs awkward multi-step playtest.

## Done criteria

- Every card in the pack has a non-stub body matching printed text (or a `ponytail:` ceiling note for missing engine support).
- `make` passes once for the whole batch.
- Session log lists the pack size and outcomes, not one card.
- Regenerate living backlogs:
  `python3 tools/stub_effect_queue.py --write-list`
  → `documentation/STUB_EFFECTS.md` (TODO stubs)
  → `documentation/PARTIAL_EFFECTS.md` (`ponytail:` ceilings — still need hooks)
