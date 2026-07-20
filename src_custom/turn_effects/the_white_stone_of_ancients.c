#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

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

u8 ShouldActivateTheWhiteStoneOfAncientsTurnEffect(void)
{
  u8 fixedDuelist;

  if (gActiveEffect.cardId != THE_WHITE_STONE_OF_ANCIENTS)
    return FALSE;

  if (gActiveEffect.turnRow != 6)
    return FALSE;

  fixedDuelist = FixedDuelistForActiveTurn();

  /* ponytail: End Phase + sent-this-turn not tracked; any GY White Stone qualifies. */
  if (!GraveyardContainsWhiteStone(fixedDuelist))
    return FALSE;

  return CanSpecialSummonBlueEyesFromDeck(ACTIVE_DUELIST);
}

void ActivateTheWhiteStoneOfAncientsTurnEffect(void)
{
  u16 cardId;
  struct DuelSummonOpts opts;

  if (!ShouldActivateTheWhiteStoneOfAncientsTurnEffect())
    return;

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

/* ponytail: banish-to-add Blue-Eyes GY effect FALSE — no once-per-turn banish hook. */
