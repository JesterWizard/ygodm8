#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"

extern u8 gWhiteStoneSentToGyThisTurn;
extern u8 gWhiteStoneSentToGyPrevTurn;

static const char sBlueEyesName[] APPEND_RODATA = "Blue-Eyes";

static u8 FixedDuelistForActiveTurn(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsBlueEyesMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sBlueEyesName);
}

static u8 GraveyardContainsWhiteStone(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == THE_WHITE_STONE_OF_ANCIENTS;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == THE_WHITE_STONE_OF_ANCIENTS)
      return TRUE;
  }

  return FALSE;
}

static u16 FindBlueEyesInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u8 i;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsBlueEyesMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanSpecialSummonBlueEyesFromDeck(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  return FindBlueEyesInDeck(turnDuelist) != CARD_NONE;
}

static void MarkWhiteStoneSentToGy(u8 controller)
{
  if (controller == DUEL_PLAYER)
    gWhiteStoneSentToGyThisTurn |= 1;
  else if (controller == DUEL_OPPONENT)
    gWhiteStoneSentToGyThisTurn |= 2;
}

static void OnWhiteStoneLeaveField(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != THE_WHITE_STONE_OF_ANCIENTS)
    return;

  MarkWhiteStoneSentToGy(ev->controller);
}

void TheWhiteStoneOfAncients_AgeSentFlags(void)
{
  gWhiteStoneSentToGyPrevTurn = gWhiteStoneSentToGyThisTurn;
  gWhiteStoneSentToGyThisTurn = 0;
}

void TheWhiteStoneOfAncients_EnsureInit(void)
{
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnWhiteStoneLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnWhiteStoneLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnWhiteStoneLeaveField);
}

u8 ShouldActivateTheWhiteStoneOfAncientsTurnEffect(void)
{
  u8 fixedDuelist;
  u8 bit;

  TheWhiteStoneOfAncients_EnsureInit();

  if (gActiveEffect.cardId != THE_WHITE_STONE_OF_ANCIENTS)
    return FALSE;

  if (gActiveEffect.turnRow != 6)
    return FALSE;

  fixedDuelist = FixedDuelistForActiveTurn();
  bit = (fixedDuelist == DUEL_PLAYER) ? 1 : 2;

  /* Engine runs turn effects at next turn start ≈ End Phase of prior turn. */
  if ((gWhiteStoneSentToGyPrevTurn & bit) == 0)
    return FALSE;

  if (!GraveyardContainsWhiteStone(fixedDuelist))
    return FALSE;

  return CanSpecialSummonBlueEyesFromDeck(ACTIVE_DUELIST);
}

void ActivateTheWhiteStoneOfAncientsTurnEffect(void)
{
  u8 fixedDuelist = FixedDuelistForActiveTurn();
  u8 bit = (fixedDuelist == DUEL_PLAYER) ? 1 : 2;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (!ShouldActivateTheWhiteStoneOfAncientsTurnEffect())
    return;

  gWhiteStoneSentToGyPrevTurn &= (u8)~bit;

  cardId = FindBlueEyesInDeck(ACTIVE_DUELIST);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(THE_WHITE_STONE_OF_ANCIENTS, 9);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts);
}

/* ponytail: GY banish → add Blue-Eyes needs GY ignition. Ceiling: banish this
 * from GY once per turn; add 1 Blue-Eyes monster from Deck to hand. */
