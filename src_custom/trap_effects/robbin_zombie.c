#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "robbin_zombie.h"

struct RobbinZombieActionData {
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

extern struct RobbinZombieActionData sActionData;

/* ponytail: mill helper does not mirror top card into graveyard; keep local mill for Robbin Zombie */
static void DiscardTopDeckCard(u8 duelist)
{
  u16 card;

  if (gDuelDecks[duelist].cardsDrawn >= NumCardsInDeck(duelist))
    return;

  card = gDuelDecks[duelist].cards[gDuelDecks[duelist].cardsDrawn];
  gDuelDecks[duelist].cardsDrawn++;
  gTurnDuelistBattleState[duelist]->graveyard = card;
}

static u8 IsRobbinZombieActiveForDuelist(u8 duelist)
{
  u8 i;
  u8 backrow = (duelist == DUEL_PLAYER) ? PLAYER_BACKROW : OPPONENT_BACKROW;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[backrow][i];
    if (zone->id == ROBBIN_ZOMBIE && zone->isFaceUp == TRUE)
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

void ApplyRobbinZombieBattleEffect(void)
{
  u8 milledDuelist;

  if (gHideEffectText)
    return;

  if (DidDuelistDealBattleDamage(DUEL_PLAYER, sActionData.id)) {
    if (!IsRobbinZombieActiveForDuelist(DUEL_PLAYER))
      return;
    milledDuelist = DUEL_OPPONENT;
  } else if (DidDuelistDealBattleDamage(DUEL_OPPONENT, sActionData.id)) {
    if (!IsRobbinZombieActiveForDuelist(DUEL_OPPONENT))
      return;
    milledDuelist = DUEL_PLAYER;
  } else {
    return;
  }

  if (gDuelDecks[milledDuelist].cardsDrawn >= NumCardsInDeck(milledDuelist))
    return;

  Duel_ShowEffectTextTyped(ROBBIN_ZOMBIE, 3);
  DiscardTopDeckCard(milledDuelist);
}

static void ActivateRobbinZombieZone(struct DuelCard *zone)
{
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  Duel_ShowEffectTextTyped(ROBBIN_ZOMBIE, 9);
}

void TryActivateRobbinZombieOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != ROBBIN_ZOMBIE || zone->isFaceUp != FALSE)
      continue;

    ActivateRobbinZombieZone(zone);
  }
}
