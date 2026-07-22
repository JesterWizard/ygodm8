#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "x_saber_airbellum.h"

struct AirbellumActionData {
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

extern struct AirbellumActionData sActionData;

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 DidAirbellumDirectBattleDamage(u8 attackerFixed)
{
  u16 damage;

  if (attackerFixed == DUEL_PLAYER) {
    if (sActionData.playerCardId != X_SABER_AIRBELLUM || sActionData.id != 4)
      return FALSE;
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  } else {
    if (sActionData.opponentCardId != X_SABER_AIRBELLUM || sActionData.id != 6)
      return FALSE;
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  }
  return damage > 0;
}

void ApplyXSaberAirbellumBattleEffect(void)
{
  u8 damagedFixed;

  if (DidAirbellumDirectBattleDamage(DUEL_PLAYER))
    damagedFixed = DUEL_OPPONENT;
  else if (DidAirbellumDirectBattleDamage(DUEL_OPPONENT))
    damagedFixed = DUEL_PLAYER;
  else
    return;

  Duel_ShowEffectTextTyped(X_SABER_AIRBELLUM, 2);
  if (Duel_CountCardsInHand(gTurnHands[TurnDuelistForFixed(damagedFixed)]) > 0)
    Duel_DiscardRandomFromHand(TurnDuelistForFixed(damagedFixed), 1, TRUE);
}

unsigned char CanActivateX_SABER_AIRBELLUM(void)
{
  if (gMonEffect.id != X_SABER_AIRBELLUM)
    return FALSE;

  /* Direct-attack discard via ApplyXSaberAirbellumBattleEffect. */
  return FALSE;
}

void ActivateX_SABER_AIRBELLUMEffect(void)
{
  Duel_ShowEffectTextTyped(X_SABER_AIRBELLUM, 2);
}
