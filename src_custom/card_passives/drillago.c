#include "global.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "drillago.h"

#define DRILLAGO_MIN_DIRECT_ATK 1600

u8 CanDrillagoAttackDirectly(u16 cardId) {
  u8 col;
  u8 hasMonster = FALSE;
  struct DuelCard *zone;

  if (cardId != DRILLAGO)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][col];
    if (zone->id != CARD_NONE)
      return FALSE;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];
    if (zone->id == CARD_NONE)
      continue;
    hasMonster = TRUE;
    if (!zone->isFaceUp)
      return FALSE;
    if (Duel_GetZoneFinalAtk(zone) < DRILLAGO_MIN_DIRECT_ATK)
      return FALSE;
  }

  return hasMonster;
}

void TryShowDrillagoDirectAttackText(u16 cardId) {
  if (CanDrillagoAttackDirectly(cardId))
    ActivatePermanentEffectCardText(DRILLAGO);
}
