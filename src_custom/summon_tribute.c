#include "global.h"
#include "summon_tribute.h"
#include "soul_exchange.h"

extern unsigned char gNumTributes;

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
