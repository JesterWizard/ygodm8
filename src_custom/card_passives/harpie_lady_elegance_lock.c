#include "global.h"
#include "common-chax.h"
#include "harpie_lady_elegance_lock.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static u8 sWindOnlyLockTurnDuelist APPEND_DATA = {0xFF};
static u8 sWindOnlyLockActive APPEND_DATA = {0};

void HarpieLadyElegance_MarkWindOnlyLock(u8 turnDuelist)
{
  sWindOnlyLockTurnDuelist = turnDuelist;
  sWindOnlyLockActive = TRUE;
}

void HarpieLadyElegance_ClearOnTurnBoundary(void)
{
  sWindOnlyLockTurnDuelist = 0xFF;
  sWindOnlyLockActive = FALSE;
}

u8 HarpieLadyElegance_BlocksSpecialSummon(u8 turnDuelist, u16 cardId)
{
  if (!sWindOnlyLockActive || turnDuelist != sWindOnlyLockTurnDuelist)
    return FALSE;

  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute != ATTRIBUTE_WIND;
}

#if !defined(__GNUC__)
void HarpieLadyEleganceLock_SelfCheck(void);
#endif

void HarpieLadyEleganceLock_SelfCheck(void)
{
  HarpieLadyElegance_MarkWindOnlyLock(ACTIVE_DUELIST);
  if (!HarpieLadyElegance_BlocksSpecialSummon(ACTIVE_DUELIST, BLUE_EYES_WHITE_DRAGON))
    return;
  if (!HarpieLadyElegance_BlocksSpecialSummon(INACTIVE_DUELIST, BLUE_EYES_WHITE_DRAGON))
    return;
  HarpieLadyElegance_ClearOnTurnBoundary();
  if (HarpieLadyElegance_BlocksSpecialSummon(ACTIVE_DUELIST, BLUE_EYES_WHITE_DRAGON))
    return;
}
