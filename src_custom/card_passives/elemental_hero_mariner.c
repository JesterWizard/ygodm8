#include "global.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "elemental_hero_mariner.h"

u8 CanElementalHeroMarinerAttackDirectly(u16 cardId)
{
  u8 col;
  struct DuelCard *zone;

  if (cardId != ELEMENTAL_HERO_MARINER)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];
    if (zone->id != CARD_NONE && !zone->isFaceUp)
      return TRUE;
  }

  return FALSE;
}

void TryShowElementalHeroMarinerDirectAttackText(u16 cardId)
{
  if (CanElementalHeroMarinerAttackDirectly(cardId))
    ActivatePermanentEffectCardText(ELEMENTAL_HERO_MARINER);
}
