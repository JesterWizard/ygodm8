#include "global.h"
#include "common-chax.h"
#include "mask_of_restrict.h"
#include "soul_exchange.h"
#include "cost_down.h"
#include "tribute.h"

extern unsigned char gNumTributes;

void ResetNumTributes(void);
int GetNumRequiredTributes(unsigned short cardId);

static int LookupRequiredTributes(u8 level)
{
  if (level <= 4)
    return 0;
  if (level <= 6)
    return 1;
  if (level <= 8)
    return 2;
  return 3;
}

int GetNumRequiredTributesWithCostDown(u16 cardId)
{
  SetCardInfo(cardId);

  if (ShouldApplyCostDownLevelForTribute(cardId))
    gCardInfo.level = GetCostDownAdjustedLevel(cardId, gCardInfo.level);

  return LookupRequiredTributes(gCardInfo.level);
}

int GetNumRequiredTributesForHandSlot(u8 handSlot, u16 cardId)
{
  SetCardInfo(cardId);

  if (ShouldApplyCostDownForHandSlot(handSlot, cardId))
    gCardInfo.level = GetCostDownAdjustedLevel(cardId, gCardInfo.level);

  return LookupRequiredTributes(gCardInfo.level);
}

LYN_REPLACE_CHECK(GetNumRequiredTributes);
int GetNumRequiredTributes__Replacement(unsigned short cardId)
{
  return GetNumRequiredTributesWithCostDown(cardId);
}

LYN_REPLACE_CHECK(ResetNumTributes);
void ResetNumTributes__Replacement(void)
{
  gNumTributes = 0;
  ClearSoulExchangeTributeCredit();
  ClearSoulExchange();
}

LYN_REPLACE_CHECK(IncrementNumTributes);
void IncrementNumTributes__Replacement(void)
{
  gNumTributes++;
}

static int SubtractPaidTributes(int requiredTributes)
{
  int paidTributes = (int)gNumTributes;

  if (gSoulExchangeTributeCredit)
    paidTributes++;

  requiredTributes -= paidTributes;

  if (requiredTributes < 0)
    requiredTributes = 0;

  if (requiredTributes > 0 && IsMaskOfRestrictActiveOnField())
    return MASK_OF_RESTRICT_TRIBUTE_BLOCK;

  return (unsigned char)requiredTributes;
}

int GetMonsterNumRequiredTributesForHandSlot(u8 handSlot, u16 cardId)
{
  int requiredTributes;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return 0;

  if (gCostDownActive && ShouldApplyCostDownForHandSlot(handSlot, cardId))
    requiredTributes = GetNumRequiredTributesForHandSlot(handSlot, cardId);
  else
    requiredTributes = GetNumRequiredTributesWithCostDown(cardId);

  return SubtractPaidTributes(requiredTributes);
}

LYN_REPLACE_CHECK(GetMonsterNumRequiredTributes);
int GetMonsterNumRequiredTributes__Replacement(unsigned short cardId)
{
  int requiredTributes;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return 0;

  requiredTributes = GetNumRequiredTributesWithCostDown(cardId);

  return SubtractPaidTributes(requiredTributes);
}
