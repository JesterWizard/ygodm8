#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateHARPIES_PET_PHANTASMAL_DRAGON(void)
{
  /* Direct attack via HarpiesPetPhantasmalDragon_CanAttackDirectly.
   * Harpie protect + End Phase detach need battle/xyz hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateHARPIES_PET_PHANTASMAL_DRAGON(void)
{
}
