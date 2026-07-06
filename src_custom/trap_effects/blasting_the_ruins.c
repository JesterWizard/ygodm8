#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "blasting_the_ruins.h"

#define BLASTING_THE_RUINS_DAMAGE 3000
#define BLASTING_THE_RUINS_MAX_DECK_CARDS 10

int NumCardsInDeck(unsigned char);
int GetCardsDrawn(unsigned char);

static u8 OwnerDeckHasAtMostTenCards(u8 owner)
{
  u16 remaining = NumCardsInDeck(owner);

  if (remaining >= GetCardsDrawn(owner))
    remaining -= GetCardsDrawn(owner);
  else
    remaining = 0;

  return remaining <= BLASTING_THE_RUINS_MAX_DECK_CARDS;
}

static void ActivateBlastingTheRuinsZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, BLASTING_THE_RUINS) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ChangeLp(ACTIVE_DUELIST, -BLASTING_THE_RUINS_DAMAGE, FALSE);
}

void TryActivateBlastingTheRuinsOnOpponentTurnStart(void)
{
  if (!OwnerDeckHasAtMostTenCards(INACTIVE_DUELIST))
    return;

  Duel_TryActivateBackrowTrapOnTurnStart(BLASTING_THE_RUINS, ActivateBlastingTheRuinsZone);
}
