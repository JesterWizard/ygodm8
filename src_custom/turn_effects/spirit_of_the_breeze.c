#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define SPIRIT_OF_THE_BREEZE_STANDBY_HEAL 1000

unsigned char ShouldActivateSpiritOfTheBreezeTurnEffect(void)
{
  return Duel_ShouldActivateTurnEffect(SPIRIT_OF_THE_BREEZE, FALSE, TRUE);
}

void ActivateSpiritOfTheBreezeTurnEffect(void)
{
  if (Duel_ChangeLp(WhoseTurn(), SPIRIT_OF_THE_BREEZE_STANDBY_HEAL, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(SPIRIT_OF_THE_BREEZE, 9);
}
