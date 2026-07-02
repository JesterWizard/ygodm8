#include "global.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "elemental_hero_knospe.h"

u8 CanElementalHeroKnospeAttackDirectly(u16 cardId)
{
  u8 col;
  struct DuelCard *zone;

  if (cardId != ELEMENTAL_HERO_KNOSPE)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    if (zone->id != CARD_NONE && zone->isFaceUp && zone->id != ELEMENTAL_HERO_KNOSPE
        && Duel_IsElementalHeroCard(zone->id))
      return TRUE;
  }

  return FALSE;
}

void TryShowElementalHeroKnospeDirectAttackText(u16 cardId)
{
  if (CanElementalHeroKnospeAttackDirectly(cardId))
    ActivatePermanentEffectCardText(ELEMENTAL_HERO_KNOSPE);
}
