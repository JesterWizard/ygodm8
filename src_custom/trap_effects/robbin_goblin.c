#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "robbin_goblin.h"

struct RobbinGoblinActionData {
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

extern struct RobbinGoblinActionData sActionData;

static u8 IsRobbinGoblinActiveForDuelist(u8 duelist)
{
  u8 i;
  u8 backrow = (duelist == DUEL_PLAYER) ? PLAYER_BACKROW : OPPONENT_BACKROW;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[backrow][i];
    if (zone->id == ROBBIN_GOBLIN && zone->isFaceUp == TRUE)
      return TRUE;
  }

  return FALSE;
}

static u8 DidDuelistDealBattleDamage(u8 duelist, u8 actionId)
{
  u16 damage;

  if (duelist == DUEL_PLAYER) {
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

void ApplyRobbinGoblinBattleEffect(void)
{
  u8 damagedDuelist;
  u8 turnDuelist;

  if (gHideEffectText)
    return;

  if (DidDuelistDealBattleDamage(DUEL_PLAYER, sActionData.id)) {
    if (!IsRobbinGoblinActiveForDuelist(DUEL_PLAYER))
      return;
    damagedDuelist = DUEL_OPPONENT;
  } else if (DidDuelistDealBattleDamage(DUEL_OPPONENT, sActionData.id)) {
    if (!IsRobbinGoblinActiveForDuelist(DUEL_OPPONENT))
      return;
    damagedDuelist = DUEL_PLAYER;
  } else {
    return;
  }

  turnDuelist = (damagedDuelist == DUEL_PLAYER) == (WhoseTurn() == DUEL_PLAYER)
      ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  if (Duel_CountCardsInHand(gTurnHands[turnDuelist]) == 0)
    return;

  Duel_ShowEffectTextTyped(ROBBIN_GOBLIN, 3);
  Duel_DiscardFromHand(turnDuelist, 1, NULL, FALSE);
}

static void ActivateRobbinGoblinZone(struct DuelCard *zone)
{
  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectTextTyped(ROBBIN_GOBLIN, 9);
}

void TryActivateRobbinGoblinOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != ROBBIN_GOBLIN || zone->isFaceUp != FALSE)
      continue;

    ActivateRobbinGoblinZone(zone);
  }
}
