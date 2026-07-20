#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "lightning_warrior.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct LightningWarriorActionData {
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

extern struct LightningWarriorActionData sActionData;

void ClearLightningWarriorPending(void)
{
  gPendingLightningWarriorDuelist = LIGHTNING_WARRIOR_PENDING_NONE;
  gPendingLightningWarriorBurn = 0;
  gPendingLightningWarriorEffectCardId = CARD_NONE;
}

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u8 FixedToTurnDuelist(u8 fixedDuelist)
{
  return (fixedDuelist == DUEL_PLAYER) == (WhoseTurn() == DUEL_PLAYER)
      ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u16 HandSizeBurnForDuelist(u8 fixedDuelist)
{
  u8 turnDuelist = FixedToTurnDuelist(fixedDuelist);
  u8 handSize = Duel_CountCardsInHand(gTurnHands[turnDuelist]);

  return (u16)handSize * 300;
}

static void MarkPendingBurn(u8 attackingDuelist, u16 effectCardId)
{
  u8 burnTarget = attackingDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u16 burn = HandSizeBurnForDuelist(burnTarget);

  if (burn == 0)
    return;

  gPendingLightningWarriorDuelist = attackingDuelist;
  gPendingLightningWarriorBurn = burn;
  gPendingLightningWarriorEffectCardId = effectCardId;
}

void ResolveLightningWarriorBattleEffect(void)
{
  u8 attackingDuelist;
  u8 burnTarget;
  u16 burn;

  attackingDuelist = gPendingLightningWarriorDuelist;
  if (attackingDuelist == LIGHTNING_WARRIOR_PENDING_NONE)
    return;

  burn = gPendingLightningWarriorBurn;
  burnTarget = attackingDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  if (gPendingLightningWarriorEffectCardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(gPendingLightningWarriorEffectCardId, 3);
  ClearLightningWarriorPending();

  if (Duel_ChangeLp(burnTarget, -(s32)burn, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}

void ApplyLightningWarriorBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId == LIGHTNING_WARRIOR
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    MarkPendingBurn(DUEL_PLAYER, LIGHTNING_WARRIOR);
  } else if (sActionData.opponentCardId == LIGHTNING_WARRIOR
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    MarkPendingBurn(DUEL_OPPONENT, LIGHTNING_WARRIOR);
  } else {
    return;
  }

  if (gUnk2023EA0.unk18 == 0)
    ResolveLightningWarriorBattleEffect();
}
