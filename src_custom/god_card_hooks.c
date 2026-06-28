#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "god_card.h"

extern unsigned short gGodCards[];

LYN_REPLACE_CHECK(IsGodCard);
unsigned IsGodCard__Replacement(unsigned short id)
{
  unsigned char i;

  if (id == BLUE_EYES_CHAOS_DRAGON)
    return 1;

  for (i = 0; gGodCards[i] != CARD_NONE; i++)
    if (gGodCards[i] == id)
      return 1;

  return 0;
}
