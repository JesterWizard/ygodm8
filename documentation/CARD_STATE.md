# CARD_STATE — latest session

**Last worked on:** 2026-07-20 — Effect data system next pass (thin checks / burns / damage-calc)

**Outcome:** Replaced leftover `Duel_Check*` call sites with `ON_FIELD_CHANGE` emits (DestroyZone + battle GY + PostBoardScan). `BURN_THROUGH_TRAPS` script op + Sparks→Meteor burn pilots in JSON. Skyscraper/Inferno subscribe to `ON_DAMAGE_CALC`.

**Open / next:** Heal-through-traps step; more damage-calc subscribers; more JSON scripts.
