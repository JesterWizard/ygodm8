#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "royal_decree.h"

void ActivateTrapEffect(u16 lp);

#define TRAP_NONE 0

static struct DuelCard *FindFaceUpRoyalDecreeOnBackrow(u8 row)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[row][i];
    if (zone != NULL && zone->id == ROYAL_DECREE && zone->isFaceUp)
      return zone;
  }

  return NULL;
}

u8 IsRoyalDecreeActiveOnField(void)
{
  if (FindFaceUpRoyalDecreeOnBackrow(PLAYER_BACKROW) != NULL)
    return TRUE;

  return FindFaceUpRoyalDecreeOnBackrow(OPPONENT_BACKROW) != NULL;
}

u8 IsRoyalDecreeNegatingTrap(u16 cardId)
{
  if (cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  return IsRoyalDecreeActiveOnField()
      && GetTypeGroup(cardId) == TYPE_GROUP_TRAP
      && cardId != ROYAL_DECREE;
}

static void ActivateRoyalDecreeAt(u8 col, u16 originCardId)
{
  gTrapEffectData.originCardId = originCardId;
  gTrapEffectData.trapZoneCol = col;
  gTrapEffectData.trapCardId = TRAP_ROYAL_DECREE;
  ActivateTrapEffect(0);
}

void EffectRoyalDecree(void)
{
  struct DuelCard *zone;

  zone = gTurnZones[PLAYER_BACKROW][gTrapEffectData.trapZoneCol];
  if (zone == NULL || zone->id != ROYAL_DECREE)
    zone = gTurnZones[OPPONENT_BACKROW][gTrapEffectData.trapZoneCol];
  if (zone == NULL || zone->id != ROYAL_DECREE)
    return;

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = ROYAL_DECREE;
    gCardEffectTextData.cardId2 = gTrapEffectData.originCardId;
    ActivateCardEffectText();
  }
}

void TryActivateRoyalDecreeOnTrapChain(void)
{
  u8 i;
  struct DuelCard *zone;

  if (GetTypeGroup(gTrapEffectData.originCardId) != TYPE_GROUP_TRAP)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone == NULL || zone->id != ROYAL_DECREE || zone->isFaceUp)
      continue;

    ActivateRoyalDecreeAt(i, gTrapEffectData.originCardId);
    return;
  }
}

void TryActivateRoyalDecreeOnRespondingTrap(void)
{
  u8 i;
  struct DuelCard *zone;
  u16 respondingTrapId;

  if (gTrapEffectData.trapCardId == TRAP_ROYAL_DECREE
      || gTrapEffectData.trapCardId == TRAP_NONE)
    return;

  zone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (zone == NULL)
    return;

  respondingTrapId = zone->id;
  if (GetTypeGroup(respondingTrapId) != TYPE_GROUP_TRAP)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];
    if (zone == NULL || zone->id != ROYAL_DECREE || zone->isFaceUp)
      continue;

    ActivateRoyalDecreeAt(i, respondingTrapId);
    return;
  }
}
