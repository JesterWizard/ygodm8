#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsLikelySpecialSummonedOpp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  /* ponytail: no SS-origin flag; face-up/ATK stand-in for Special Summoned. */
  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]) < 0)
    return FALSE;

  return IsLikelySpecialSummonedOpp(gFixedZones[fixedRow][fixedCol]);
}

static u8 FieldHasTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(INACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) != DUEL_ACTION_OK)
    return;

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

  *outRow = INACTIVE_DUELIST_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(INACTIVE_DUELIST_MONSTER_ROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateHARPIE_CONDUCTOR(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HARPIE_CONDUCTOR)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HARPIE_CONDUCTOR)
    return FALSE;

  /* ponytail: name Lady + protect destroy redirect + on-Harpie-return trigger need
   * name/destroy/return hooks. Ceiling: OPT bounce 1 face-up/ATK opp monster. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateHARPIE_CONDUCTOREffect(void)
{
  Duel_ShowEffectTextTyped(HARPIE_CONDUCTOR, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
