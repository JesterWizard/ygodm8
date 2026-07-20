#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define CANNONHOLDER_DAMAGE 700

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 IsGravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGravekeepersName);
}

static u8 IsValidTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != gMonEffect.row)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (zone->id == GRAVEKEEPERS_CANNONHOLDER)
    return FALSE;

  return IsGravekeeperMonster(zone->id);
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

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTributeTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -CANNONHOLDER_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTributeTarget(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateGRAVEKEEPERS_CANNONHOLDER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRAVEKEEPERS_CANNONHOLDER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRAVEKEEPERS_CANNONHOLDER)
    return FALSE;

  return CanUseMonsterEffect(zone) && FieldHasTributeTarget();
}

void ActivateGRAVEKEEPERS_CANNONHOLDEREffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_CANNONHOLDER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTributeTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
