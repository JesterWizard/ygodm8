#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_GAIODIAZ(void)
{
  /* Battle DEF burn via ApplyGladiatorBeastPermanentBattleEffects; tag-out via CanActivateGLADIATOR_BEAST_GAIODIAZ. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_GAIODIAZ(void)
{
}
