#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 IsGladiatorBeastCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static u8 IsGladiatorBeastHandCard(u16 cardId)
{
  return IsGladiatorBeastCard(cardId);
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 FindGladiatorBeastMonsterInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorBeastCard(cardId) && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER)
      return cardId;
  }

  return CARD_NONE;
}

static u8 HandHasGladiatorBeast(u8 turnDuelist)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];
  u8 maxSlots = MAX_ZONES_IN_ROW;
  u8 i;

  for (i = 0; i < maxSlots; i++) {
    if (IsGladiatorBeastCard(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

unsigned char ShouldActivateGLADIATOR_BEAST_TYGERIUS(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != GLADIATOR_BEAST_TYGERIUS)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  return FindGladiatorBeastMonsterInDeck(duelist) != CARD_NONE;
}

void ActivateGLADIATOR_BEAST_TYGERIUS(void)
{
  u8 duelist;
  struct DuelCard *zone;
  u16 searchId;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_TYGERIUS, 8);
  if (IsDuelOver() == TRUE)
    return;

  if (HandHasGladiatorBeast(duelist))
    Duel_DiscardFromHand(duelist, 1, IsGladiatorBeastHandCard, TRUE);

  searchId = FindGladiatorBeastMonsterInDeck(duelist);
  if (searchId != CARD_NONE)
    Duel_AddDeckCardToHand(duelist, searchId, TRUE);

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  zone->unk4 = 1;
}
