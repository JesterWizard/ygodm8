#include "global.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_OPPONENT 16
#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_LOSER_PLAYER 4

struct ChaosMaxActionData {
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

extern struct ChaosMaxActionData sActionData;

static u8 IsMonsterFieldRow(u8 turnRow) {
  return turnRow == 1 || turnRow == 2;
}

static u8 CardHasHarmfulTargetImmunityOnField(u16 cardId) {
  if (cardId == GRAVEKEEPERS_HERATIC && Duel_IsBackrowCardOnField(NECROVALLEY, TRUE))
    return TRUE;

  return cardId == BLUE_EYES_CHAOS_MAX_DRAGON
      || cardId == BLUE_EYES_SHINING_DRAGON
      || cardId == THE_UNSTOPPABLE_EXODIA_INCARNATE
      || cardId == THE_WINGED_DRAGON_OF_RA_SPHERE_MODE
      || cardId == LYRILUSC_INDEPENDENT_NIGHTINGALE
      || cardId == SILENT_SWORDSMAN_LV3;
}

u8 IsImmuneToHarmfulTargetedEffectsOnField(u16 cardId, u8 turnRow) {
  if (!IsMonsterFieldRow(turnRow))
    return FALSE;

  return CardHasHarmfulTargetImmunityOnField(cardId);
}

u8 HasDoublePiercingBattleDamage(u16 cardId) {
  return cardId == BLUE_EYES_CHAOS_MAX_DRAGON;
}

static void ApplyPiercingDamageToOpponent(u16 damage) {
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

static void ApplyPiercingDamageToPlayer(u16 damage) {
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

void ApplyBlueEyesChaosMaxDragonDoublePiercingDamage(void) {
  u16 attackerAtk;
  u16 defenderDef;
  u16 damage;

  if (sActionData.id == 2) {
    if (!HasDoublePiercingBattleDamage(sActionData.playerCardId))
      return;
    if (!(sActionData.flags & FLAG_GRAVEYARD_OPPONENT))
      return;

    attackerAtk = sActionData.playerCardAtkOrLifePointsMod;
    defenderDef = sActionData.opponentCardDefense;
    if (attackerAtk <= defenderDef)
      return;

    damage = (attackerAtk - defenderDef) * 2;
    ApplyPiercingDamageToOpponent(damage);
    return;
  }

  if (sActionData.id == 5) {
    if (!HasDoublePiercingBattleDamage(sActionData.opponentCardId))
      return;
    if (!(sActionData.flags & FLAG_GRAVEYARD_PLAYER))
      return;

    attackerAtk = sActionData.opponentCardAtkOrLifePointsMod;
    defenderDef = sActionData.playerCardDefense;
    if (attackerAtk <= defenderDef)
      return;

    damage = (attackerAtk - defenderDef) * 2;
    ApplyPiercingDamageToPlayer(damage);
  }
}
