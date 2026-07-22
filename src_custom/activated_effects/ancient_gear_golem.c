#include "global.h"
#include "common-chax.h"
#include "ancient_gear_tanker.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct AncientGearGolemActionData {
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

extern struct AncientGearGolemActionData sActionData;

static u8 IsGolemAttacker(u16 cardId)
{
  return cardId == ANCIENT_GEAR_GOLEM
      || cardId == ULTIMATE_ANCIENT_GEAR_GOLEM
      || cardId == ANCIENT_GEAR_GOLEM_ULTIMATE_POUND
      || cardId == ANCIENT_GEAR_GADJILTRON_DRAGON
      || cardId == ANCIENT_GEAR_MEGATON_GOLEM;
}

static void ApplyPiercingDamageToOpponent(u16 damage)
{
  if (damage == 0)
    return;
  if (gDuelLifePoints[DUEL_OPPONENT] <= damage) {
    gDuelLifePoints[DUEL_OPPONENT] = 0;
    sActionData.flags |= FLAG_LOSER_OPPONENT;
  } else {
    gDuelLifePoints[DUEL_OPPONENT] -= damage;
  }
  gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

static void ApplyPiercingDamageToPlayer(u16 damage)
{
  if (damage == 0)
    return;
  if (gDuelLifePoints[DUEL_PLAYER] <= damage) {
    gDuelLifePoints[DUEL_PLAYER] = 0;
    sActionData.flags |= FLAG_LOSER_PLAYER;
  } else {
    gDuelLifePoints[DUEL_PLAYER] -= damage;
  }
  gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
}

static u8 AttackerHasPierce(u16 cardId, u8 fixedRow, u8 col)
{
  struct DuelCard *zone;

  if (IsGolemAttacker(cardId))
    return TRUE;

  zone = gFixedZones[fixedRow][col];
  return AncientGearMonsterHasPierceMark(zone);
}

void ApplyAncientGearGolemPiercingBattleEffect(void)
{
  u16 atk;
  u16 def;

  if (sActionData.id == 2 && AttackerHasPierce(sActionData.playerCardId,
                                               sActionData.playerMonsterRow, sActionData.unkA)
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    atk = sActionData.playerCardAtkOrLifePointsMod;
    def = sActionData.opponentCardDefense;
    if (atk > def)
      ApplyPiercingDamageToOpponent(atk - def);
    return;
  }

  if (sActionData.id == 5 && AttackerHasPierce(sActionData.opponentCardId,
                                               sActionData.opponentMonsterRow, sActionData.unk16)
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    atk = sActionData.opponentCardAtkOrLifePointsMod;
    def = sActionData.playerCardDefense;
    if (atk > def)
      ApplyPiercingDamageToPlayer(atk - def);
  }
}

unsigned char CanActivateANCIENT_GEAR_GOLEM(void)
{
  if (gMonEffect.id != ANCIENT_GEAR_GOLEM)
    return FALSE;

  /* Attack S/T lock via AncientGear_AttackerBlocksOppSpellTrap;
   * pierce via ApplyAncientGearGolemPiercingBattleEffect. */
  return FALSE;
}

void ActivateANCIENT_GEAR_GOLEMEffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_GEAR_GOLEM, 2);
}
