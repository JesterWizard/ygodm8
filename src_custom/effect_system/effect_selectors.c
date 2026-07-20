#include "global.h"
#include "common-chax.h"
#include "duel.h"
#include "effect_conditions.h"
#include "effect_selectors.h"

static const u8 sFieldRows[] __attribute__((section(".text"))) = {
  PLAYER_MONSTER_ROW,
  OPPONENT_MONSTER_ROW,
  PLAYER_BACKROW,
  OPPONENT_BACKROW,
};

u8 EffectSel_FirstInRows(const u8 *rows, u8 rowCount, PickZoneValidator validate,
                         u8 *outRow, u8 *outCol)
{
  u8 r;
  u8 col;

  if (rows == NULL || validate == NULL || outRow == NULL || outCol == NULL)
    return FALSE;

  for (r = 0; r < rowCount; r++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!validate(rows[r], col))
        continue;
      *outRow = rows[r];
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

u8 EffectSel_ExistsInRows(const u8 *rows, u8 rowCount, PickZoneValidator validate)
{
  u8 row;
  u8 col;

  return EffectSel_FirstInRows(rows, rowCount, validate, &row, &col);
}

u8 EffectSel_FirstOnField(PickZoneValidator validate, u8 *outRow, u8 *outCol)
{
  return EffectSel_FirstInRows(sFieldRows, ARRAY_COUNT(sFieldRows), validate, outRow, outCol);
}

u8 EffectSel_ExistsOnField(PickZoneValidator validate)
{
  u8 row;
  u8 col;

  return EffectSel_FirstOnField(validate, &row, &col);
}

u8 EffectSel_AiPickFirst(u8 *outRow, u8 *outCol)
{
  if (gPickZoneState.validator == NULL)
    return FALSE;
  return EffectSel_FirstOnField(gPickZoneState.validator, outRow, outCol);
}

u8 EffectSel_FirstByCond(u8 condId, u8 *outRow, u8 *outCol)
{
  EffectCondFn fn = EffectCond_Get(condId);

  if (fn == NULL)
    return FALSE;
  return EffectSel_FirstOnField(fn, outRow, outCol);
}

u8 EffectSel_ExistsByCond(u8 condId)
{
  EffectCondFn fn = EffectCond_Get(condId);

  if (fn == NULL)
    return FALSE;
  return EffectSel_ExistsOnField(fn);
}
