#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define ULTIMATE_OFFERING_LP_COST 500

extern struct DuelCard gSelectedCard;

void UnlockCardsInRow(unsigned char turnRow);
void LockMonsterCardsInRow(unsigned char turnRow);

extern u8 gUltimateOfferingExtraSummonPending;
extern u8 gUltimateOfferingExtraSummonUsed;

u8 IsActivatedUltimateOfferingZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == ULTIMATE_OFFERING && zone->isFaceUp == TRUE;
}

static u8 BackrowHasFaceUpUltimateOffering(u8 backrow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsActivatedUltimateOfferingZone(gFixedZones[backrow][i]))
      return TRUE;
  }

  return FALSE;
}

u8 IsUltimateOfferingActiveForActiveDuelist(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return BackrowHasFaceUpUltimateOffering(PLAYER_BACKROW);

  return BackrowHasFaceUpUltimateOffering(OPPONENT_BACKROW);
}

static u8 ActiveDuelistCanPayUltimateOfferingCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= ULTIMATE_OFFERING_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= ULTIMATE_OFFERING_LP_COST;
}

u8 CanUseUltimateOfferingExtraSummon(void)
{
  if (!gUltimateOfferingExtraSummonPending)
    return FALSE;

  if (gUltimateOfferingExtraSummonUsed)
    return FALSE;

  if (!IsUltimateOfferingActiveForActiveDuelist())
    return FALSE;

  return ActiveDuelistCanPayUltimateOfferingCost();
}

void TryUnlockHandForUltimateOfferingExtraSummon(void)
{
  if (!CanUseUltimateOfferingExtraSummon())
    return;

  UnlockCardsInRow(ACTIVE_DUELIST_HAND);
}

u8 TryPayUltimateOfferingCost(void)
{
  if (!ActiveDuelistCanPayUltimateOfferingCost())
    return FALSE;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -ULTIMATE_OFFERING_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return FALSE;

  return TRUE;
}

void ResetUltimateOfferingTurnState(void)
{
  gUltimateOfferingExtraSummonPending = FALSE;
  gUltimateOfferingExtraSummonUsed = FALSE;
}

void AgeUltimateOfferingSetFlags(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];
    if (zone->id == ULTIMATE_OFFERING && zone->unk4 != 0)
      zone->unk4 = 0;
  }
}

void MarkUltimateOfferingJustSet(struct DuelCard *zone)
{
  if (zone->id == ULTIMATE_OFFERING)
    zone->unk4 = 1;
}

unsigned char ShouldActivateUltimateOfferingTurnEffect(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_BACKROW)
    return FALSE;
  if (gActiveEffect.col != GetFirstCardMatchZoneId(gTurnZones[ACTIVE_DUELIST_BACKROW], ULTIMATE_OFFERING))
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->id == ULTIMATE_OFFERING && !zone->isFaceUp && zone->unk4 == 0;
}

void ActivateUltimateOfferingTurnEffect(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  Duel_ShowEffectTextTyped(ULTIMATE_OFFERING, 9);
}

static u8 IsMonsterHandToFieldPlacement(void)
{
  return gDuelCursor.currentY == ACTIVE_DUELIST_MONSTER_ROW
      && gDuelCursor.destY == ACTIVE_DUELIST_HAND
      && GetTypeGroup(gSelectedCard.id) == TYPE_GROUP_MONSTER;
}

u8 TryConsumeUltimateOfferingExtraSummonPayment(void)
{
  if (!IsMonsterHandToFieldPlacement())
    return TRUE;

  if (gUltimateOfferingExtraSummonUsed)
    return FALSE;

  if (!gUltimateOfferingExtraSummonPending)
    return TRUE;

  if (!TryPayUltimateOfferingCost())
    return FALSE;

  gUltimateOfferingExtraSummonPending = FALSE;
  gUltimateOfferingExtraSummonUsed = TRUE;
  LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);

  return TRUE;
}

void TryEnableUltimateOfferingExtraSummonAfterPlacement(void)
{
  if (!IsMonsterHandToFieldPlacement())
    return;

  if (!IsUltimateOfferingActiveForActiveDuelist())
    return;

  if (gUltimateOfferingExtraSummonUsed)
    return;

  if (gUltimateOfferingExtraSummonPending)
    return;

  if (!ActiveDuelistCanPayUltimateOfferingCost())
    return;

  gUltimateOfferingExtraSummonPending = TRUE;
  UnlockCardsInRow(ACTIVE_DUELIST_HAND);
}
