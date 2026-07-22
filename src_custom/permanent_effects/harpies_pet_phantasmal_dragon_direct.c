#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "harpies_pet_phantasmal_dragon.h"

u8 HarpiesPetPhantasmalDragon_CanAttackDirectly(const struct DuelCard *zone)
{
  return zone != NULL && zone->isFaceUp && zone->id == HARPIES_PET_PHANTASMAL_DRAGON;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HarpiesPetPhantasmalDragon_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = HARPIES_PET_PHANTASMAL_DRAGON;
  zone.isFaceUp = TRUE;
  if (HarpiesPetPhantasmalDragon_CanAttackDirectly(&zone) == FALSE)
    __builtin_trap();
}
#endif
