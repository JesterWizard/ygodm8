#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

unsigned char CanActivateGAGAGIGO_THE_RISEN(void)
{
  if (gMonEffect.id != GAGAGIGO_THE_RISEN)
    return FALSE;

  /* No printed monster effect (Xyz materials only). Not field-ignition. */
  return FALSE;
}

void ActivateGAGAGIGO_THE_RISENEffect(void)
{
  /* No printed monster effect (Xyz materials only). Not field-ignition. */
  Duel_ShowEffectTextTyped(GAGAGIGO_THE_RISEN, 2);
}
