#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGLADIATOR_BEAST_ALEXANDER(void)
{
  /* Spell immunity via IsImmuneToSpellEffectsOnField; tag-out via CanActivateGLADIATOR_BEAST_ALEXANDER. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGLADIATOR_BEAST_ALEXANDER(void)
{
}
