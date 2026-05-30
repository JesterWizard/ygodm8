#include "global.h"
#include "common-chax.h"
#include "soul_exchange.h"
#include "tribute.h"

extern unsigned char gNumTributes;

void ResetNumTributes(void);
int GetNumRequiredTributes(unsigned short cardId);

LYN_REPLACE_CHECK(ResetNumTributes);
void ResetNumTributes__Replacement(void)
{
  gNumTributes = 0;
  ClearSoulExchangeTributeCredit();
  ClearSoulExchange();
}

LYN_REPLACE_CHECK(GetMonsterNumRequiredTributes);
int GetMonsterNumRequiredTributes__Replacement(unsigned short cardId)
{
  int requiredTributes;
  int paidTributes;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return 0;

  requiredTributes = GetNumRequiredTributes(cardId);
  paidTributes = (int)gNumTributes;

  if (gSoulExchangeTributeCredit)
    paidTributes++;

  requiredTributes -= paidTributes;

  if (requiredTributes < 0)
    requiredTributes = 0;

  return (unsigned char)requiredTributes;
}
