#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "gladiator_beast_battled.h"

#define DEFINE_GB_DECK_TAG_OUT(cardId)                                           \
  unsigned char CanActivate##cardId(void)                                      \
  {                                                                            \
    struct DuelCard *zone;                                                     \
                                                                               \
    if (gMonEffect.id != cardId)                                               \
      return FALSE;                                                            \
                                                                               \
    zone = gTurnZones[gMonEffect.row][gMonEffect.zone];                        \
    return GladiatorBeast_CanActivateDeckTagOut(cardId, zone);                  \
  }                                                                            \
                                                                               \
  void Activate##cardId##Effect(void)                                            \
  {                                                                            \
    struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];       \
                                                                               \
    Duel_ShowEffectTextTyped(cardId, 2);                                       \
    GladiatorBeast_ActivateDeckTagOut(self, cardId);                           \
  }

DEFINE_GB_DECK_TAG_OUT(GLADIATOR_BEAST_RETIARI)
DEFINE_GB_DECK_TAG_OUT(GLADIATOR_BEAST_OCTAVIUS)
DEFINE_GB_DECK_TAG_OUT(GLADIATOR_BEAST_TYGERIUS)
DEFINE_GB_DECK_TAG_OUT(GLADIATOR_BEAST_SPARTACUS)
DEFINE_GB_DECK_TAG_OUT(GLADIATOR_BEAST_SAMNITE)
DEFINE_GB_DECK_TAG_OUT(GLADIATOR_BEAST_DIMACARI)
DEFINE_GB_DECK_TAG_OUT(GLADIATOR_BEAST_ALEXANDER)
DEFINE_GB_DECK_TAG_OUT(GLADIATOR_BEAST_GAIODIAZ)

unsigned char CanActivateGLADIATOR_BEAST_TORAX(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GLADIATOR_BEAST_TORAX)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  return GladiatorBeast_CanActivateTagOutDraw(GLADIATOR_BEAST_TORAX, zone);
}

void ActivateGLADIATOR_BEAST_TORAXEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_TORAX, 2);
  GladiatorBeast_ActivateDeckTagOutDraw(self, GLADIATOR_BEAST_TORAX);
}
