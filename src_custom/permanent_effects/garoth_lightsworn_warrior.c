#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "garoth_lightsworn_warrior.h"

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

#define GAROTH_MILL_COUNT 2

static u8 sGarothMillReentry APPEND_DATA = 0;

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

static u8 IsLightswornCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 DeckRemaining(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  if (deckSize <= top)
    return 0;

  return (u8)(deckSize - top);
}

static u8 CountLightswornAmongTop(u8 turnDuelist, u8 count)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u8 ls = 0;

  for (i = 0; i < count; i++) {
    if (IsLightswornCard(gDuelDecks[fixedDuelist].cards[top + i]))
      ls++;
  }

  return ls;
}

unsigned char ShouldActivateGAROTH_LIGHTSWORN_WARRIOR(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != GAROTH_LIGHTSWORN_WARRIOR)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  return DeckRemaining(duelist) > 0;
}

void ActivateGAROTH_LIGHTSWORN_WARRIOR(void)
{
  u8 duelist;
  u8 millCount;
  u8 drawCount;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  millCount = DeckRemaining(duelist);
  if (millCount > GAROTH_MILL_COUNT)
    millCount = GAROTH_MILL_COUNT;

  Duel_ShowEffectTextTyped(GAROTH_LIGHTSWORN_WARRIOR, 8);
  if (IsDuelOver() == TRUE)
    return;

  if (millCount == 0)
    return;

  drawCount = CountLightswornAmongTop(duelist, millCount);

  if (Duel_MillTopDeckCards(duelist, millCount, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (drawCount > 0) {
    if (Duel_DrawCards(duelist, drawCount, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  zone->unk4 = 1;
  /* On-summon stand-in; other-LS deck mills via TryApplyGarothAfterDeckMill. */
}

static u8 ControllerHasFaceUpGaroth(u8 fixedDuelist)
{
  u8 row = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == GAROTH_LIGHTSWORN_WARRIOR)
      return TRUE;
  }

  return FALSE;
}

void TryApplyGarothAfterDeckMill(u8 turnDuelist, u8 millCount)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 garothMill;
  u8 drawCount;

  if (sGarothMillReentry || millCount == 0 || IsDuelOver() == TRUE)
    return;

  if (!ControllerHasFaceUpGaroth(fixedDuelist))
    return;

  garothMill = DeckRemaining(turnDuelist);
  if (garothMill > GAROTH_MILL_COUNT)
    garothMill = GAROTH_MILL_COUNT;
  if (garothMill == 0)
    return;

  drawCount = CountLightswornAmongTop(turnDuelist, garothMill);

  sGarothMillReentry = TRUE;
  Duel_ShowEffectTextTyped(GAROTH_LIGHTSWORN_WARRIOR, 8);
  if (Duel_MillTopDeckCards(turnDuelist, garothMill, TRUE) == DUEL_ACTION_DUEL_OVER) {
    sGarothMillReentry = FALSE;
    return;
  }

  if (drawCount > 0)
    Duel_DrawCards(turnDuelist, drawCount, TRUE);

  sGarothMillReentry = FALSE;
}
