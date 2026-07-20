#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

#define MORAY_OF_GREED_RETURN_COUNT 2
#define MORAY_OF_GREED_DRAW_COUNT 3

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsWaterMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_WATER;
}

static u8 CountWaterMonstersInHand(struct DuelCard **handRow)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsWaterMonster(handRow[i]->id))
      count++;
  }

  return count;
}

u8 CanActivateMORAY_OF_GREED(void)
{
  return CountWaterMonstersInHand(gTurnHands[ACTIVE_DUELIST]) >= MORAY_OF_GREED_RETURN_COUNT;
}

static s8 PickWaterMonsterHandZone(struct DuelCard **handRow)
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(handRow, IsWaterMonster);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsWaterMonster(handRow[i]->id))
      return i;
  }

  return -1;
}

static void ReturnHandCardToDeck(u8 turnDuelist, u8 handZone)
{
  struct DuelCard *handCard = gTurnHands[turnDuelist][handZone];
  u16 cardId = handCard->id;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  ClearZone(handCard);

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static void MORAY_OF_GREED_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 returned;
  s8 handZone;

  if (!CanActivateMORAY_OF_GREED())
    return;

  Duel_ShowEffectText(MORAY_OF_GREED);

  if (IsDuelOver() == TRUE)
    return;

  for (returned = 0; returned < MORAY_OF_GREED_RETURN_COUNT; returned++) {
    handZone = PickWaterMonsterHandZone(handRow);
    if (handZone < 0)
      return;

    ReturnHandCardToDeck(ACTIVE_DUELIST, (u8)handZone);
  }

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  if (Duel_DrawCards(ACTIVE_DUELIST, MORAY_OF_GREED_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectMORAY_OF_GREED(void)
{
  if (!CanActivateMORAY_OF_GREED()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MORAY_OF_GREED, MORAY_OF_GREED_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
