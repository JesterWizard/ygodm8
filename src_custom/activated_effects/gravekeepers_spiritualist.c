#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGRAVEKEEPERS_SPIRITUALIST(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_SPIRITUALIST)
    return FALSE;

  /* Necrovalley-gated Spellcaster Fusion from Extra Deck needs fusion
   * summon API outside this file. Not field-ignition. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_SPIRITUALISTEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_SPIRITUALIST, 2);
}
