#include "global.h"
#include "common-chax.h"
#include "amazoness_princess.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

u8 GetDuelistForZone(struct DuelCard *zone);

static const char sAmazonessName[] APPEND_RODATA = "Amazoness";

static u8 IsAmazonessSpellTrap(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sAmazonessName);
}

static u16 FindAmazonessSpellTrapInDeck(u8 fixedDuelist)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsAmazonessSpellTrap(cardId))
      return cardId;
  }

  return CARD_NONE;
}

void TryAmazonessPrincessOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  u16 cardId;

  if (zone == NULL || zone->id != AMAZONESS_PRINCESS)
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist == 0xFF)
    return;

  turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
      ? ACTIVE_DUELIST
      : INACTIVE_DUELIST;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  cardId = FindAmazonessSpellTrapInDeck(fixedDuelist);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(AMAZONESS_PRINCESS, 8);
  Duel_AddDeckCardToHand(turnDuelist, cardId, TRUE);
}
