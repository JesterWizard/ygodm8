#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsFaceUpEffectMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!IsCardFaceUp(zone))
    return FALSE;

  SetCardInfo(zone->id);
  return gCardInfo.color == COLOR_EFFECT;
}

static u8 IsValidNegateTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow > PLAYER_MONSTER_ROW)
    return FALSE;

  return IsFaceUpEffectMonster(gFixedZones[fixedRow][fixedCol]);
}

static u8 FieldHasNegateTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidNegateTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidNegateTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  /* ponytail: until end of turn clear needs EOT unk4 reset hook. */
  zone->unk4 |= 0x80;

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
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidNegateTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (row = PLAYER_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidNegateTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateNEHSHADDOLL_GENIUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != NEHSHADDOLL_GENIUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != NEHSHADDOLL_GENIUS)
    return FALSE;

  /* ponytail: FLIP Shaddoll unaffected + sent-by-effect branches need flip/send
   * hooks. Ceiling: OPT negate 1 face-up Effect Monster (unk4). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasNegateTarget();
}

void ActivateNEHSHADDOLL_GENIUSEffect(void)
{
  Duel_ShowEffectTextTyped(NEHSHADDOLL_GENIUS, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidNegateTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
