#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_double_dude.h"
#include "duel_helpers.h"
#include "the_dark_door.h"

void TryUnlockDestinyHeroDoubleDudeForSecondAttack(struct DuelCard *attacker)
{
  if (attacker == NULL || attacker->id != DESTINY_HERO_DOUBLE_DUDE)
    return;
  if (IsTheDarkDoorActiveOnField())
    return;

  if (attacker->effectUsedThisTurn == FALSE) {
    attacker->effectUsedThisTurn = TRUE;
    attacker->isLocked = FALSE;
  }
}

unsigned char ShouldActivateDESTINY_HERO_DOUBLE_DUDE(void)
{
  /* Double attack live via TryUnlockDestinyHeroDoubleDudeForSecondAttack.
   * ponytail: destroyed Standby 2 Tokens need turn/token hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateDESTINY_HERO_DOUBLE_DUDE(void)
{
}
