#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "gift_of_the_mystical_elf.h"

#define GIFT_OF_THE_MYSTICAL_ELF_LP_PER_MONSTER 300

static void ActivateGiftOfTheMysticalElfZone(struct DuelCard *zone)
{
  u8 monsterCount = Duel_CountFixedMonstersMatching(NULL);
  u16 heal;

  if (Duel_ActivateContinuousTrapPreamble(zone, GIFT_OF_THE_MYSTICAL_ELF) == DUEL_ACTION_DUEL_OVER)
    return;

  if (monsterCount == 0)
    return;

  heal = (u16)monsterCount * GIFT_OF_THE_MYSTICAL_ELF_LP_PER_MONSTER;
  Duel_ChangeLp(INACTIVE_DUELIST, heal, FALSE);
}

void TryActivateGiftOfTheMysticalElfOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(GIFT_OF_THE_MYSTICAL_ELF, ActivateGiftOfTheMysticalElfZone);
}
