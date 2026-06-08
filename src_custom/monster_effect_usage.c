#include "global.h"
#include "common-chax.h"
#include "monster_effect_usage.h"

extern const u8 gCardEffectUsage_Hook[];
extern const u8 gCardLockAfterActivation_Hook[];

u8 GetCardEffectUsage(u16 cardId)
{
  if (cardId >= NUM_TOTAL_CARDS)
    return EFFECT_USAGE_NONE;

  return gCardEffectUsage_Hook[cardId];
}

u8 CanUseMonsterEffect(struct DuelCard *zone)
{
  switch (GetCardEffectUsage(zone->id)) {
    case EFFECT_USAGE_ONCE:
      return zone->effectExhausted == FALSE;
    case EFFECT_USAGE_ONCE_PER_TURN:
      return zone->effectUsedThisTurn == FALSE;
    case EFFECT_USAGE_MULTIPLE_PER_TURN:
      return TRUE;
    case EFFECT_USAGE_CONTINUOUS:
      return FALSE;
    case EFFECT_USAGE_NONE:
    default:
      return TRUE;
  }
}

void MarkMonsterEffectUsed(struct DuelCard *zone)
{
  switch (GetCardEffectUsage(zone->id)) {
    case EFFECT_USAGE_ONCE:
      zone->effectExhausted = TRUE;
      break;
    case EFFECT_USAGE_ONCE_PER_TURN:
      zone->effectUsedThisTurn = TRUE;
      break;
    case EFFECT_USAGE_MULTIPLE_PER_TURN:
    case EFFECT_USAGE_CONTINUOUS:
    case EFFECT_USAGE_NONE:
    default:
      break;
  }

  if (gCardLockAfterActivation_Hook[zone->id])
    zone->isLocked = TRUE;
}
