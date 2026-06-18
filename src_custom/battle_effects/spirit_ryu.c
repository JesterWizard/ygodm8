#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spirit_ryu.h"

struct SpiritRyuActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct SpiritRyuActionData sActionData;

static u8 CardIsDragon(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_DRAGON;
}

static u8 IsMonsterVsMonsterBattle(void)
{
  return sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 5
      || sActionData.id == 6;
}

static u16 BoostAtk(u16 atk)
{
  return Duel_ClampStat((u32)atk + SPIRIT_RYU_ATK_BOOST);
}

void TryApplySpiritRyuToPendingAction(void)
{
  if (!IsMonsterVsMonsterBattle())
    return;

  if (sActionData.playerCardId == SPIRIT_RYU
      && !CardIsDragon(sActionData.opponentCardId)) {
    sActionData.playerCardAtkOrLifePointsMod =
        BoostAtk(sActionData.playerCardAtkOrLifePointsMod);
  }

  if (sActionData.opponentCardId == SPIRIT_RYU
      && !CardIsDragon(sActionData.playerCardId)) {
    sActionData.opponentCardAtkOrLifePointsMod =
        BoostAtk(sActionData.opponentCardAtkOrLifePointsMod);
  }
}
