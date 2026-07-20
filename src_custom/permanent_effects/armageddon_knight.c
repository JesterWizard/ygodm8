#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDarkMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].attribute == ATTRIBUTE_SHADOW;
}

static u16 FindDarkMonsterInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsDarkMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanSendDarkFromDeck(u8 turnDuelist)
{
  return FindDarkMonsterInDeck(turnDuelist) != CARD_NONE;
}

static u8 SendDarkFromDeckToGraveyard(u8 turnDuelist)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u16 cardId;
  s16 deckIndex;

  cardId = FindDarkMonsterInDeck(turnDuelist);
  if (cardId == CARD_NONE)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(turnDuelist, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  GraveyardExpand_PushTurn(turnDuelist, cardId);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return TRUE;
}

unsigned char ShouldActivateARMAGEDDON_KNIGHT(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != ARMAGEDDON_KNIGHT)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  return CanSendDarkFromDeck(duelist);
}

void ActivateARMAGEDDON_KNIGHT(void)
{
  u8 duelist;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(ARMAGEDDON_KNIGHT, 8);
  SendDarkFromDeckToGraveyard(duelist);

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  zone->unk4 = 1;
}
