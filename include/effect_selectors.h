#ifndef GUARD_EFFECT_SELECTORS_H
#define GUARD_EFFECT_SELECTORS_H

#include "global.h"
#include "duel_helpers.h"

/* Selector registry (Phase 2). First-match / exists scans over conditions.
 * See documentation/effect-data-system.md.
 */

enum EffectSelId {
  EFFECT_SEL_FIRST_MATCH = 0,
  EFFECT_SEL_EXISTS,
  EFFECT_SEL_COUNT
};

u8 EffectSel_FirstInRows(const u8 *rows, u8 rowCount, PickZoneValidator validate,
                         u8 *outRow, u8 *outCol);
u8 EffectSel_ExistsInRows(const u8 *rows, u8 rowCount, PickZoneValidator validate);
u8 EffectSel_FirstOnField(PickZoneValidator validate, u8 *outRow, u8 *outCol);
u8 EffectSel_ExistsOnField(PickZoneValidator validate);

/* AI picker compatible with Duel_SetupPickZone aiPicker.
 * Uses gPickZoneState.validator set by Duel_SetupPickZone. */
u8 EffectSel_AiPickFirst(u8 *outRow, u8 *outCol);

/* Convenience: first/exists using a registered condition id. */
u8 EffectSel_FirstByCond(u8 condId, u8 *outRow, u8 *outCol);
u8 EffectSel_ExistsByCond(u8 condId);

#endif /* GUARD_EFFECT_SELECTORS_H */
