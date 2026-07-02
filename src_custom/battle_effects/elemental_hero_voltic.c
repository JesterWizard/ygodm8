#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_voltic.h"

struct ElementalHeroVolticActionData {
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

extern struct ElementalHeroVolticActionData sActionData;

static u8 IsPlayerAttackAction(u8 id)
{
  return id == 1 || id == 2 || id == 4;
}

static u8 IsOpponentAttackAction(u8 id)
{
  return id == 5 || id == 6;
}

static u8 DidVolticDealBattleDamage(u8 *attackerTurnDuelist)
{
  u16 damage;

  if (IsPlayerAttackAction(sActionData.id)
      && sActionData.playerCardId == ELEMENTAL_HERO_VOLTIC) {
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
    if (damage == 0)
      return FALSE;
    *attackerTurnDuelist = ACTIVE_DUELIST;
    return TRUE;
  }

  if (IsOpponentAttackAction(sActionData.id)
      && sActionData.opponentCardId == ELEMENTAL_HERO_VOLTIC) {
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
    if (damage == 0)
      return FALSE;
    *attackerTurnDuelist = INACTIVE_DUELIST;
    return TRUE;
  }

  return FALSE;
}

void ApplyElementalHeroVolticBattleEffect(void)
{
  u8 attackerTurnDuelist;

  if (gHideEffectText)
    return;

  if (!DidVolticDealBattleDamage(&attackerTurnDuelist))
    return;

  /* ponytail: no banished-zone / removed-from-play storage yet — show text only;
     optional target + special summon deferred until banish zone exists. */
  (void)attackerTurnDuelist;
  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_VOLTIC, 3);
}
