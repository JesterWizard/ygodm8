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

  Duel_ActivateContinuousZone(zone);

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(GIFT_OF_THE_MYSTICAL_ELF, 3);

  if (IsDuelOver() == TRUE || monsterCount == 0)
    return;

  heal = (u16)monsterCount * GIFT_OF_THE_MYSTICAL_ELF_LP_PER_MONSTER;
  Duel_ChangeLp(INACTIVE_DUELIST, heal, FALSE);
}

void TryActivateGiftOfTheMysticalElfOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != GIFT_OF_THE_MYSTICAL_ELF || zone->isFaceUp != FALSE)
      continue;

    ActivateGiftOfTheMysticalElfZone(zone);
    if (IsDuelOver() == TRUE)
      return;
  }
}
