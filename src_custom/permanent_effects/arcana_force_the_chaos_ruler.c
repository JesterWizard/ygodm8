#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

extern const CardData gCardData_NEW[];

static const char sArcanaForceName[] APPEND_RODATA = "Arcana Force";
static const char sCoinNameNeedle[] APPEND_RODATA = "Coin";

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsArcanaForceMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sArcanaForceName);
}

static u8 IsKnownCoinTossCard(u16 cardId)
{
  switch (cardId) {
  case CUP_OF_ACE:
  case ACE_OF_SWORD:
  case SECOND_COIN_TOSS:
  case ARCANA_SPREAD:
  case ARCANA_READING:
  case TIME_WIZARD:
  case FAIRY_BOX:
  case BLOWBACK_DRAGON:
  case LIGHT_BARRIER:
    return TRUE;
  default:
    return FALSE;
  }
}

static u8 IsCoinTossCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (IsArcanaForceMonster(cardId))
    return TRUE;

  if (Duel_CardNameContains(cardId, sCoinNameNeedle))
    return TRUE;

  return IsKnownCoinTossCard(cardId);
}

static u8 IsArcanaForceLevel10(u16 cardId)
{
  if (!IsArcanaForceMonster(cardId))
    return FALSE;

  return gCardData_NEW[cardId].level == 10;
}

static u16 FindArcanaForceLevel10InDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsArcanaForceLevel10(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindCoinTossCardInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsCoinTossCard(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindAnyArcanaForceInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsArcanaForceMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanResolveCoinEffect(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (FindArcanaForceLevel10InDeck(turnDuelist) != CARD_NONE
      && FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0)
    return TRUE;

  if (FindCoinTossCardInDeck(turnDuelist) != CARD_NONE
      && FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0)
    return TRUE;

  return FindAnyArcanaForceInDeck(turnDuelist) != CARD_NONE
      && FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0;
}

unsigned char ShouldActivateARCANA_FORCE_THE_CHAOS_RULER(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != ARCANA_FORCE_THE_CHAOS_RULER)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  /* ponytail: true trigger is Special Summon; on-summon coin stand-in covers SS path. */
  return CanResolveCoinEffect(duelist);
}

void ActivateARCANA_FORCE_THE_CHAOS_RULER(void)
{
  u8 duelist;
  struct DuelCard *zone;
  u16 cardId;
  struct DuelSummonOpts opts;
  u8 heads;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(ARCANA_FORCE_THE_CHAOS_RULER, 8);
  if (IsDuelOver() == TRUE)
    return;

  heads = RandRangeU8(0, 1) == 1;
  if (heads) {
    cardId = FindArcanaForceLevel10InDeck(duelist);
    if (cardId != CARD_NONE) {
      opts = Duel_DefaultSpecialSummonOpts(TRUE);
      Duel_SpecialSummonFromDeck(duelist, cardId, opts);
    }
  } else {
    cardId = FindCoinTossCardInDeck(duelist);
    if (cardId == CARD_NONE)
      cardId = FindAnyArcanaForceInDeck(duelist);
    if (cardId != CARD_NONE && FirstEmptyZoneInRow(gTurnHands[duelist]) >= 0)
      Duel_AddDeckCardToHand(duelist, cardId, TRUE);
  }

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone != NULL)
    zone->unk4 = 1;
  /* ponytail: Light Barrier opp-activation lock needs continuous field hook. */
}
