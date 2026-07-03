#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_inferno.h"

#define INFERNO_WATER_BATTLE_ATK_BOOST 1000

struct ElementalHeroInfernoActionData {
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

extern struct ElementalHeroInfernoActionData sActionData;

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

void ApplyElementalHeroInfernoBattleAtkBoost(void)
{
  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId == ELEMENTAL_HERO_INFERNO
      && sActionData.opponentCardId != CARD_NONE
      && sActionData.opponentCardAttribute == ATTRIBUTE_WATER) {
    sActionData.playerCardAtkOrLifePointsMod = Duel_ClampStat(
        (u32)sActionData.playerCardAtkOrLifePointsMod + INFERNO_WATER_BATTLE_ATK_BOOST);
  }

  if (sActionData.opponentCardId == ELEMENTAL_HERO_INFERNO
      && sActionData.playerCardId != CARD_NONE
      && sActionData.playerCardAttribute == ATTRIBUTE_WATER) {
    sActionData.opponentCardAtkOrLifePointsMod = Duel_ClampStat(
        (u32)sActionData.opponentCardAtkOrLifePointsMod + INFERNO_WATER_BATTLE_ATK_BOOST);
  }
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroInferno_SelfCheck(void)
{
  struct ElementalHeroInfernoActionData saved = sActionData;

  sActionData.id = 1;
  sActionData.playerCardId = ELEMENTAL_HERO_INFERNO;
  sActionData.playerCardAtkOrLifePointsMod = 2300;
  sActionData.opponentCardId = ELEMENTAL_HERO_BUBBLEMAN;
  sActionData.opponentCardAttribute = ATTRIBUTE_WATER;
  ApplyElementalHeroInfernoBattleAtkBoost();
  if (sActionData.playerCardAtkOrLifePointsMod != 3300)
    while (1)
      ;

  sActionData = saved;
}
#endif
