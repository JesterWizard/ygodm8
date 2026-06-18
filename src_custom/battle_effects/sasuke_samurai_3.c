#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "sasuke_samurai_3.h"

struct SasukeSamurai3ActionData {
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

extern struct SasukeSamurai3ActionData sActionData;

void ClearSasukeSamurai3DrawPending(void)
{
  gPendingSasukeSamurai3DrawDuelist = SASUKE_SAMURAI_3_DRAW_PENDING_NONE;
}

static u8 DidSasukeSamurai3DealBattleDamage(u8 *damagedFixedDuelist)
{
  u16 damage;

  if (sActionData.playerCardId == SASUKE_SAMURAI_3) {
    if (sActionData.id != 2 && sActionData.id != 4)
      return FALSE;
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
    if (damage == 0)
      return FALSE;
    *damagedFixedDuelist = DUEL_OPPONENT;
    return TRUE;
  }

  if (sActionData.opponentCardId == SASUKE_SAMURAI_3) {
    if (sActionData.id != 5 && sActionData.id != 6)
      return FALSE;
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
    if (damage == 0)
      return FALSE;
    *damagedFixedDuelist = DUEL_PLAYER;
    return TRUE;
  }

  return FALSE;
}

void ApplySasukeSamurai3BattleEffect(void)
{
  u8 damagedFixedDuelist;

  if (gHideEffectText)
    return;

  if (!DidSasukeSamurai3DealBattleDamage(&damagedFixedDuelist))
    return;

  gPendingSasukeSamurai3DrawDuelist = damagedFixedDuelist;

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveSasukeSamurai3BattleEffect();
}

void ResolveSasukeSamurai3BattleEffect(void)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  fixedDuelist = gPendingSasukeSamurai3DrawDuelist;
  if (fixedDuelist == SASUKE_SAMURAI_3_DRAW_PENDING_NONE)
    return;

  gPendingSasukeSamurai3DrawDuelist = SASUKE_SAMURAI_3_DRAW_PENDING_NONE;

  turnDuelist = Duel_TurnDuelistMatchingWhoseTurn(fixedDuelist);
  if (Duel_CountCardsInHand(gTurnHands[turnDuelist]) >= SASUKE_SAMURAI_3_TARGET_HAND)
    return;

  Duel_ShowEffectTextTyped(SASUKE_SAMURAI_3, 3);
  if (IsDuelOver() == TRUE)
    return;

  Duel_DrawCardsUntilHandSize(turnDuelist, SASUKE_SAMURAI_3_TARGET_HAND, TRUE);
}
