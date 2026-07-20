#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateWULF_LIGHTSWORN_BEAST(void)
{
  /* ponytail: milled-from-Deck Special Summon needs mill/deck-send hook. */
  return FALSE;
}

void ActivateWULF_LIGHTSWORN_BEAST(void)
{
}
