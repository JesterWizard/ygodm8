#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
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

static u8 CountCardsInDuelistHand(u8 duelist)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gDuel.hands[duelist][i].id != CARD_NONE)
      count++;

  return count;
}

static u8 PickRandomHandZone(u8 duelist)
{
  u8 i;
  u8 occupied = CountCardsInDuelistHand(duelist);
  u8 chosen;
  u8 seen = 0;

  if (occupied == 0)
    return 0xFF;

  chosen = RandRangeU8(0, occupied - 1);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gDuel.hands[duelist][i].id == CARD_NONE)
      continue;

    if (seen == chosen)
      return i;

    seen++;
  }

  return 0xFF;
}

static void DiscardRandomHandCard(u8 duelist)
{
  u8 zone = PickRandomHandZone(duelist);

  if (zone == 0xFF)
    return;

  ClearZoneAndSendMonToGraveyard(&gDuel.hands[duelist][zone], duelist);
}

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

static void ShowRobbinGoblinEffectText(void)
{
  if (gHideEffectText)
    return;

  ResetCardEffectTextData();
  SetCardEffectTextType(3);
  gCardEffectTextData.cardId = ROBBIN_GOBLIN;
  ActivateCardEffectText();
}

void ApplyRobbinGoblinBattleEffect(void)
{
  u8 damagedDuelist;

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

  if (CountCardsInDuelistHand(damagedDuelist) == 0)
    return;

  ShowRobbinGoblinEffectText();
  DiscardRandomHandCard(damagedDuelist);
}

static void ActivateRobbinGoblinZone(struct DuelCard *zone)
{
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(9);
    gCardEffectTextData.cardId = ROBBIN_GOBLIN;
    ActivateCardEffectText();
  }
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
