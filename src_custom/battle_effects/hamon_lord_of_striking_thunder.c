#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "hamon_lord_of_striking_thunder.h"

#define FLAG_GRAVEYARD_PLAYER   1
#define FLAG_GRAVEYARD_OPPONENT 2
#define HAMON_BATTLE_PENDING_NONE 0xFF

struct HamonBattleActionData {
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

extern struct HamonBattleActionData sActionData;
extern u8 gHideEffectText;

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

void ResolveHamonLordOfStrikingThunderBattleEffect(void)
{
  u8 attackerDuelist;
  u8 burnTarget;

  attackerDuelist = gPendingHamonBattleBurnDuelist;
  if (attackerDuelist == HAMON_BATTLE_PENDING_NONE)
    return;

  if (gPendingHamonBattleBurnEffectCardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(gPendingHamonBattleBurnEffectCardId, 3);

  gPendingHamonBattleBurnDuelist = HAMON_BATTLE_PENDING_NONE;
  gPendingHamonBattleBurnEffectCardId = CARD_NONE;

  burnTarget = (attackerDuelist == DUEL_PLAYER) ? DUEL_OPPONENT : DUEL_PLAYER;
  Duel_ChangeLp(burnTarget, -HAMON_BATTLE_BURN_DAMAGE, TRUE);
}

void ApplyHamonLordOfStrikingThunderBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId == HAMON_LORD_OF_STRIKING_THUNDER
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    gPendingHamonBattleBurnDuelist = DUEL_PLAYER;
    gPendingHamonBattleBurnEffectCardId = HAMON_LORD_OF_STRIKING_THUNDER;
  } else if (sActionData.opponentCardId == HAMON_LORD_OF_STRIKING_THUNDER
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    gPendingHamonBattleBurnDuelist = DUEL_OPPONENT;
    gPendingHamonBattleBurnEffectCardId = HAMON_LORD_OF_STRIKING_THUNDER;
  } else {
    return;
  }

  if (gUnk2023EA0.unk18 == 0)
    ResolveHamonLordOfStrikingThunderBattleEffect();
}
