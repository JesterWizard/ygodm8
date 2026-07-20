#include "global.h"
#include "common-chax.h"
#include "amazoness_fighting_spirit.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"

#define AMAZONESS_FIGHTING_SPIRIT_BATTLE_ATK_BOOST 1000

struct AmazonessFightingSpiritActionData {
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

extern struct AmazonessFightingSpiritActionData sActionData;

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u8 IsPlayerAttackAction(u8 id)
{
  return id == 1 || id == 2 || id == 4;
}

static u8 IsOpponentAttackAction(u8 id)
{
  return id == 5 || id == 6;
}

void ApplyAmazonessFightingSpiritBattleAtkBoost(void)
{
  u8 attackerDuelist;
  u16 attackerCardId;
  u16 *attackerAtk;
  u16 defenderCardId;
  u16 defenderAtk;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (IsPlayerAttackAction(sActionData.id)) {
    attackerDuelist = DUEL_PLAYER;
    attackerCardId = sActionData.playerCardId;
    attackerAtk = &sActionData.playerCardAtkOrLifePointsMod;
    defenderCardId = sActionData.opponentCardId;
    defenderAtk = sActionData.opponentCardAtkOrLifePointsMod;
  } else if (IsOpponentAttackAction(sActionData.id)) {
    attackerDuelist = DUEL_OPPONENT;
    attackerCardId = sActionData.opponentCardId;
    attackerAtk = &sActionData.opponentCardAtkOrLifePointsMod;
    defenderCardId = sActionData.playerCardId;
    defenderAtk = sActionData.playerCardAtkOrLifePointsMod;
  } else {
    return;
  }

  if (Duel_FindBackrowCard(attackerDuelist, AMAZONESS_FIGHTING_SPIRIT, TRUE) == NULL)
    return;
  if (!Duel_IsAmazonessCard(attackerCardId) || defenderCardId == CARD_NONE)
    return;
  if (defenderAtk <= *attackerAtk)
    return;

  *attackerAtk = Duel_ClampStat((u32)(*attackerAtk) + AMAZONESS_FIGHTING_SPIRIT_BATTLE_ATK_BOOST);
}
