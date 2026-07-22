#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOppDestroyableMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasOppMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppDestroyableMonster(OPPONENT_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOppDestroyableMonster(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
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

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppDestroyableMonster(OPPONENT_MONSTER_ROW, col)) {
      *outRow = OPPONENT_MONSTER_ROW;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateMILLENNIUM_EYES_RESTRICT(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MILLENNIUM_EYES_RESTRICT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MILLENNIUM_EYES_RESTRICT)
    return FALSE;

  /* chain equip/absorb opp Effect Monster needs chain/control hooks.
   * OPT destroy 1 opp monster. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOppMonster();
}

void ActivateMILLENNIUM_EYES_RESTRICTEffect(void)
{
  Duel_ShowEffectTextTyped(MILLENNIUM_EYES_RESTRICT, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOppDestroyableMonster, ResolveDestroyTarget, CancelTargeting,
                     AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
