#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "harpie_perfumer.h"

extern u8 gCyberShieldTargets[];
u16 sub_803F04C(unsigned char arg0);

/* Equip only to Harpie Lady or Sisters — include name=HL forms. */
LYN_REPLACE_CHECK(ConditionCyberShield);
u32 ConditionCyberShield__Replacement(u16 cardId)
{
  struct DuelCard probe;

  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == HARPIE_LADY || cardId == HARPIE_LADY_1 || cardId == HARPIE_LADY_2
      || cardId == HARPIE_LADY_3 || cardId == HARPIE_LADY_SISTERS
      || cardId == CYBER_HARPIE || cardId == CYBER_SLASH_HARPIE_LADY
      || cardId == CYBER_SLASH_HARPY_LADY)
    return TRUE;

  probe.id = cardId;
  probe.isFaceUp = TRUE;
  probe.isDefending = FALSE;
  probe.isLocked = FALSE;
  probe.unkTwo = 0;
  probe.unkThree = 0;
  probe.unk4 = 0;
  probe.willChangeSides = FALSE;
  if (HarpiePerfumer_TreatsNameAsHarpieLady(&probe))
    return TRUE;

  return (gCyberShieldTargets[cardId >> 3] & sub_803F04C(cardId & 7)) != 0;
}
