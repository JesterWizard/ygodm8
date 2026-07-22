#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsValidTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != gMonEffect.row)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return zone->id != DESTINY_HERO_DASHER;
}

static u8 FieldHasTributeTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTributeTarget(gMonEffect.row, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTributeTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* Ceiling: battle DEF change + draw-phase GY SS need battle/draw hooks.
   * OPT tribute 1 other → +2 tempStage (~1000 ATK until EP via ResetTempStagesForAllCards). */
  if (self->tempStage < 126)
    self->tempStage += 2;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTributeTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 bestCol = 0;
  u8 found = FALSE;
  u16 lowestAtk = 0xFFFF;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidTributeTarget(*outRow, col))
      continue;

    zone = gFixedZones[*outRow][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (!found || atk < lowestAtk) {
      found = TRUE;
      lowestAtk = atk;
      bestCol = col;
    }
  }

  if (!found)
    return FALSE;

  *outCol = bestCol;
  return TRUE;
}

unsigned char CanActivateDESTINY_HERO_DASHER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_DASHER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DASHER)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTributeTarget();
}

void ActivateDESTINY_HERO_DASHEREffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_DASHER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTributeTarget, ResolveTributeTarget, CancelTargeting,
                     AiPickTributeTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
