# Deferred Effects Backlog

Auto-generated living list of **engine gaps** still called out in effect-file comments (plain notes after `Ceiling:`/`ponytail:` soft-clears).
Use this to pick an engine surface and batch the cards that wait on it.
Stubs: [`STUB_EFFECTS.md`](STUB_EFFECTS.md). Ceiling markers: [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md). Migration: [`effect-data-system.md`](effect-data-system.md).

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials + deferred
```

**Last updated:** 2026-07-22 22:07 UTC  
**Files with deferred notes:** `0`  
**Notes tagged:** `0`

## Suggested tackle order

Difficulty order (easiest first) within the current surface work:

1. **Already-wired comment clears** — notes that only restate live hooks (Honest MP return, Dynatag/Dominance battle Apply*, Earfon PickZone).
2. **Single-target PickZone / trunk pick** — Dystopia on-SS GY pick, Chicken Game L/R+A 3-way.
3. **Sequential PickZone** — Brionac bounce-N, Gungnir destroy-2, Double Cyclone.
4. **OnSummon residuals** — Empress / Desire / Marine Dolphin / Sagittarii draw.
5. **OnBattleDestroy** — bump `EFFECT_EVENT_MAX_SUBSCRIBERS` first (23/24 full), then Dreamer timing / Vassal / Lantron / Turbo Synchron.
6. **Hard UI** — multi-select (Amulet/Magnolia), look+reorder (Dominance), reveal excavate (Smartfon/Telefon), DeckMenu+PickZone crash (Athena/Dark Armed).
7. **Post-battle softlocks** — Core / Ice Edge / Sunrise (needs main-loop queue).
8. **Hard deferred** — `chain.Negate`, Extra Deck / Pendulum, `gate.SendCost`, equip API (Armory Arm), win-on-summon (Holactie).

Tag fan-out reminder: `ui.Choice` / `event.OnSummon` / `event.OnDestroy` / `gate.Tribute` before Extra Deck / full chain.

## Counts by missing surface

| Tag | Notes | Cards | Suggested phase |
|-----|------:|------:|-----------------|
| **total** | **0** | **0** | |
