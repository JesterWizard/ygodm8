#include "global.h"
#include "summon_tribute.h"
#include "soul_exchange.h"
#include "tribute.h"

extern unsigned char gNumTributes;
extern struct DuelCursor gDuelCursor;

void RecordPendingSummonTributeCount(void)
{
  u8 tributeCount;

  tributeCount = gNumTributes;
  if (gSoulExchangeTributeCredit)
    tributeCount++;

  gPendingSummonTributeCount = tributeCount;
}

void SetPendingSummonTributeCount(u8 tributeCount)
{
  gPendingSummonTributeCount = tributeCount;
}

void ClearPendingSummonTributeCount(void)
{
  gPendingSummonTributeCount = 0;
}

u8 GetPendingSummonTributeCount(void)
{
  return gPendingSummonTributeCount;
}

void SetPendingTributeSummonCardId(u16 cardId)
{
  gPendingTributeSummonCardId = cardId;
}

void ClearPendingTributeSummonCardId(void)
{
  gPendingTributeSummonCardId = CARD_NONE;
}

u16 GetPendingTributeSummonCardId(void)
{
  return gPendingTributeSummonCardId;
}

u8 PendingTributeSummonStillUnpaid(void)
{
  u16 pendingId = GetPendingTributeSummonCardId();
  u8 i;

  if (pendingId == CARD_NONE)
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[PLAYER_HAND][i]->id == pendingId)
      return GetMonsterNumRequiredTributesForHandSlot(i, pendingId) > 0;
  }

  return GetMonsterNumRequiredTributes(pendingId) > 0;
}

u16 ResolveTributeSummonTarget(void)
{
  u16 summonCardId = GetPendingTributeSummonCardId();

  if (summonCardId != CARD_NONE)
    return summonCardId;

  if (gDuelCursor.destY == PLAYER_HAND)
    return gFixedZones[PLAYER_HAND][gDuelCursor.destX]->id;

  return CARD_NONE;
}

void ClearDoubleCostonDarkBonusPaid(void)
{
  gDoubleCostonDarkBonusPaid = 0;
}

void RecordDoubleCostonDarkBonusPaid(u8 bonusPaid)
{
  gDoubleCostonDarkBonusPaid += bonusPaid;
}

u8 GetDoubleCostonDarkBonusPaid(void)
{
  return gDoubleCostonDarkBonusPaid;
}
