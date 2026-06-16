#include "global.h"
#include "constants/card_ids.h"
#include "constants/card_enums.h"
#include "cost_down.h"
#include "duel_helpers.h"
#include "summon_tribute.h"
#include "tribute.h"

extern unsigned char gNumTributes;

u8 CardQualifiesForDoubleCostonDarkBonus(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.attribute != ATTRIBUTE_SHADOW)
    return FALSE;
  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return GetNumRequiredTributesWithCostDown(cardId) >= 2;
}

static u8 HandHasDarkMonsterNeedingTwoTributes(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 handId = gFixedZones[PLAYER_HAND][i]->id;

    if (handId == CARD_NONE)
      continue;

    if (CardQualifiesForDoubleCostonDarkBonus(handId))
      return TRUE;
  }

  return FALSE;
}

u8 DoubleCostonCoversDarkTributeSummon(u16 summonCardId, u16 tributeCardId)
{
  if (tributeCardId != DOUBLE_COSTON || summonCardId == CARD_NONE)
    return FALSE;

  return CardQualifiesForDoubleCostonDarkBonus(summonCardId);
}

unsigned char GetKaiserSeaHorseTributeCount(u16 cardId) {
  if (cardId == KAISER_SEA_HORSE)
    return 2;

  return 1;
}

void AddTributeCredit(u16 tributeCardId)
{
  gNumTributes += GetKaiserSeaHorseTributeCount(tributeCardId);

  if (tributeCardId == DOUBLE_COSTON && HandHasDarkMonsterNeedingTwoTributes())
    RecordDoubleCostonDarkBonusPaid(1);
}
