#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

unsigned char ShouldActivateGRINDER_GOLEM(void)
{
  /* ponytail: hand SS to opp field + Grinder Tokens + NS/Set lock need summon/token hooks. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGRINDER_GOLEM(void)
{
}
