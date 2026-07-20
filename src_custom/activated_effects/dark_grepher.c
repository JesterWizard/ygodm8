#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDarkMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_SHADOW;
}

static u8 IsLevel5PlusDarkMonster(u16 cardId)
{
  if (!IsDarkMonster(cardId))
    return FALSE;

  return gCardInfo.level >= 5;
}

static u8 IsGrepherHandCost(u16 cardId)
{
  return IsLevel5PlusDarkMonster(cardId) && cardId != DARK_GREPHER;
}

static u8 HandHasDarkMonster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsDarkMonster(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 HandHasGrepherHandCost(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsGrepherHandCost(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static s16 FindDeckDarkIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsDarkMonster(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 DeckHasDarkMonster(void)
{
  return FindDeckDarkIndex() >= 0;
}

static u8 MillOneDarkFromDeck(void)
{
  s16 deckIndex = FindDeckDarkIndex();
  u8 fixedDuelist;
  u16 cardId;

  if (deckIndex < 0)
    return FALSE;

  fixedDuelist = FixedDuelistForActive();
  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
  return TRUE;
}

static s8 FindHandZoneWithId(u16 cardId)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == cardId)
      return (s8)i;
  }

  return -1;
}

unsigned char CanActivateDARK_GREPHER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DARK_GREPHER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DARK_GREPHER)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return HandHasDarkMonster() && DeckHasDarkMonster();
}

void ActivateDARK_GREPHEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(DARK_GREPHER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, IsDarkMonster, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (!MillOneDarkFromDeck())
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonDarkGrepherFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != DARK_GREPHER)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HandHasGrepherHandCost();
}

u8 TrySpecialSummonDarkGrepherFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 grepherZone;

  if (!CanSpecialSummonDarkGrepherFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DARK_GREPHER, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, IsGrepherHandCost, TRUE) != DUEL_ACTION_OK)
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  grepherZone = FindHandZoneWithId(DARK_GREPHER);
  if (grepherZone < 0)
    return FALSE;

  return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, grepherZone, opts) == DUEL_ACTION_OK;
}
