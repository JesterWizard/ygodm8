#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "gladiator_beast_battled.h"

/* Tag-out → SS 2 different GB from Deck via GladiatorBeast_CanActivateDeckTagOutTwo. */

unsigned char CanActivateGLADIATOR_BEAST_NEROKIUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GLADIATOR_BEAST_NEROKIUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  return GladiatorBeast_CanActivateDeckTagOutTwo(GLADIATOR_BEAST_NEROKIUS, zone);
}

void ActivateGLADIATOR_BEAST_NEROKIUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_NEROKIUS, 2);
  GladiatorBeast_ActivateDeckTagOutTwo(self, GLADIATOR_BEAST_NEROKIUS);
}
