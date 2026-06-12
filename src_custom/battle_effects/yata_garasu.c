#include "global.h"
#include "common-chax.h"
#include "yata_garasu.h"

struct YataGarasuActionData {
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

extern struct YataGarasuActionData sActionData;

void ResetYataGarasuSkipDraw(void) {
  gYataGarasuSkipDrawDuelist = YATA_GARASU_SKIP_DRAW_NONE;
}

u8 ShouldSkipDrawPhaseForYataGarasu(u8 turn) {
  return gYataGarasuSkipDrawDuelist == turn;
}

void ConsumeYataGarasuSkipDraw(u8 turn) {
  if (gYataGarasuSkipDrawDuelist == turn)
    gYataGarasuSkipDrawDuelist = YATA_GARASU_SKIP_DRAW_NONE;
}

static u8 DidYataGarasuDealBattleDamage(u16 attackerCardId, u8 actionId, u8 damagedDuelist) {
  u16 damage;

  if (attackerCardId != YATA_GARASU)
    return FALSE;

  if (damagedDuelist == DUEL_OPPONENT) {
    if (actionId != 2 && actionId != 4)
      return FALSE;
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  } else {
    if (actionId != 5 && actionId != 6)
      return FALSE;
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  }

  return damage > 0;
}

void ApplyYataGarasuBattleEffect(void) {
  if (gHideEffectText)
    return;

  if (DidYataGarasuDealBattleDamage(sActionData.playerCardId, sActionData.id, DUEL_OPPONENT)) {
    gYataGarasuSkipDrawDuelist = DUEL_OPPONENT;
    return;
  }

  if (DidYataGarasuDealBattleDamage(sActionData.opponentCardId, sActionData.id, DUEL_PLAYER))
    gYataGarasuSkipDrawDuelist = DUEL_PLAYER;
}
