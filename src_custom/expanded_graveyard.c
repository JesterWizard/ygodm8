#include "global.h"
#include "common-chax.h"
#include "ai_sim.h"
#include "configs/runtime.h"
#include "duel.h"
#include "expanded_graveyard.h"

extern u16 gExpandedGraveyard[2][EXPANDED_GRAVEYARD_CAPACITY];

void PlaceMonsterCardInZone(u16 *zone, u16 card);

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

static u8 GraveyardZoneToFixedDuelist(u16 *zone)
{
  if (zone == &gDuel.duelistbattleState[DUEL_PLAYER].graveyard)
    return DUEL_PLAYER;
  if (zone == &gDuel.duelistbattleState[DUEL_OPPONENT].graveyard)
    return DUEL_OPPONENT;
  return 0xFF;
}

static u8 CountFromArray(u8 fixedDuelist)
{
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++) {
    if (gExpandedGraveyard[fixedDuelist][i] == CARD_NONE)
      return i;
  }
  return EXPANDED_GRAVEYARD_CAPACITY;
}

static void SyncLegacyTop(u8 fixedDuelist)
{
  u8 count;

  count = CountFromArray(fixedDuelist);
  if (count == 0)
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
  else
    gDuel.duelistbattleState[fixedDuelist].graveyard =
        gExpandedGraveyard[fixedDuelist][count - 1];
}

void GraveyardExpand_SyncLegacyTop(u8 fixedDuelist)
{
  if (fixedDuelist > DUEL_OPPONENT || !GraveyardExpand_IsEnabled())
    return;

  SyncLegacyTop(fixedDuelist);
}

u8 GraveyardExpand_IsEnabled(void)
{
  return gRuntimeConfig.expand_graveyard == TRUE;
}

void GraveyardExpand_Init(void)
{
  u8 duelist;
  u8 i;

  for (duelist = 0; duelist < 2; duelist++) {
    for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
      gExpandedGraveyard[duelist][i] = CARD_NONE;
  }
}

void GraveyardExpand_SyncFromTurnStart(void)
{
  u8 duelist;

  if (!GraveyardExpand_IsEnabled())
    return;

  for (duelist = 0; duelist < 2; duelist++)
    SyncLegacyTop(duelist);
  GraveyardExpand_RefreshDisplay();
}

void GraveyardExpand_SyncAllLegacyTops(void)
{
  u8 duelist;

  if (!GraveyardExpand_IsEnabled())
    return;

  for (duelist = 0; duelist < 2; duelist++)
    SyncLegacyTop(duelist);
}

void GraveyardExpand_CopyStacks(u16 *dst)
{
  u16 i;

  for (i = 0; i < 2 * EXPANDED_GRAVEYARD_CAPACITY; i++)
    dst[i] = ((u16 *)gExpandedGraveyard)[i];
}

void GraveyardExpand_LoadStacks(const u16 *src)
{
  u16 i;

  for (i = 0; i < 2 * EXPANDED_GRAVEYARD_CAPACITY; i++)
    ((u16 *)gExpandedGraveyard)[i] = src[i];
}

static u8 DeckCardsRemaining(u8 fixedDuelist)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 drawn = gDuelDecks[fixedDuelist].cardsDrawn;

  if (deckSize >= drawn)
    return deckSize - drawn;
  return 0;
}

void GraveyardExpand_ClearOpponentAfterSimIfFirstTurn(void)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return;

  /* ponytail: DECK_SIZE(40) minus opening hand(5) = 35; re-tune if deck size changes. */
  if (DeckCardsRemaining(DUEL_OPPONENT) != DECK_SIZE - 5)
    return;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gExpandedGraveyard[DUEL_OPPONENT][i] = CARD_NONE;
  SyncLegacyTop(DUEL_OPPONENT);
  GraveyardExpand_RefreshDisplay();
}

void GraveyardExpand_PushFixed(u8 fixedDuelist, u16 cardId)
{
  u8 i;
  u8 count;

  if (fixedDuelist > DUEL_OPPONENT || cardId == CARD_NONE)
    return;

  /* ponytail: expanded GY lives outside gDuel snapshot; skip during AI sim. */
  if (AiSimSuppressesGraveyardMutations())
    return;

  if (!GraveyardExpand_IsEnabled()) {
    if (AiSimSuppressesGraveyardMutations())
      return;
    gDuel.duelistbattleState[fixedDuelist].graveyard = cardId;
    return;
  }

  count = CountFromArray(fixedDuelist);
  if (count >= EXPANDED_GRAVEYARD_CAPACITY) {
    /* ponytail: 40-card cap matches deck size; on overflow, drop oldest. */
    for (i = 1; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
      gExpandedGraveyard[fixedDuelist][i - 1] = gExpandedGraveyard[fixedDuelist][i];
    count = EXPANDED_GRAVEYARD_CAPACITY - 1;
  }

  gExpandedGraveyard[fixedDuelist][count] = cardId;
  SyncLegacyTop(fixedDuelist);
}

void GraveyardExpand_PushTurn(u8 turnDuelist, u16 cardId)
{
  GraveyardExpand_PushFixed(TurnDuelistToFixed(turnDuelist), cardId);
}

u16 GraveyardExpand_PopFixed(u8 fixedDuelist)
{
  u8 count;
  u16 cardId;

  if (fixedDuelist > DUEL_OPPONENT)
    return CARD_NONE;

  if (AiSimSuppressesGraveyardMutations())
    return CARD_NONE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    return cardId;
  }

  count = CountFromArray(fixedDuelist);
  if (count == 0)
    return CARD_NONE;

  count--;
  cardId = gExpandedGraveyard[fixedDuelist][count];
  gExpandedGraveyard[fixedDuelist][count] = CARD_NONE;
  SyncLegacyTop(fixedDuelist);
  return cardId;
}

u16 GraveyardExpand_PopTurn(u8 turnDuelist)
{
  return GraveyardExpand_PopFixed(TurnDuelistToFixed(turnDuelist));
}

u8 GraveyardExpand_GetCount(u8 fixedDuelist)
{
  if (fixedDuelist > DUEL_OPPONENT)
    return 0;
  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == CARD_NONE ? 0 : 1;
  return CountFromArray(fixedDuelist);
}

u16 GraveyardExpand_GetCardAt(u8 fixedDuelist, u8 index)
{
  if (fixedDuelist > DUEL_OPPONENT || index >= GraveyardExpand_GetCount(fixedDuelist))
    return CARD_NONE;
  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard;
  return gExpandedGraveyard[fixedDuelist][index];
}

u16 GraveyardExpand_RemoveAtFixed(u8 fixedDuelist, u8 index)
{
  u8 count;
  u16 cardId;
  u8 i;

  if (fixedDuelist > DUEL_OPPONENT)
    return CARD_NONE;

  if (AiSimSuppressesGraveyardMutations())
    return CARD_NONE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    return cardId;
  }

  count = CountFromArray(fixedDuelist);
  if (index >= count)
    return CARD_NONE;

  cardId = gExpandedGraveyard[fixedDuelist][index];
  for (i = index; i + 1 < count; i++)
    gExpandedGraveyard[fixedDuelist][i] = gExpandedGraveyard[fixedDuelist][i + 1];
  gExpandedGraveyard[fixedDuelist][count - 1] = CARD_NONE;
  SyncLegacyTop(fixedDuelist);
  return cardId;
}

u16 GraveyardExpand_RemoveAtTurn(u8 turnDuelist, u8 index)
{
  return GraveyardExpand_RemoveAtFixed(TurnDuelistToFixed(turnDuelist), index);
}

LYN_REPLACE_CHECK(PlaceMonsterCardInZone);
void PlaceMonsterCardInZone__Replacement(u16 *zone, u16 card)
{
  u8 fixedDuelist;

  if (GetTypeGroup(card) != TYPE_GROUP_MONSTER)
    return;

  fixedDuelist = GraveyardZoneToFixedDuelist(zone);
  if (fixedDuelist <= DUEL_OPPONENT && GraveyardExpand_IsEnabled()) {
    GraveyardExpand_PushFixed(fixedDuelist, card);
    return;
  }

  *zone = card;
}

LYN_REPLACE_CHECK(GetGraveCardAndClearGrave2);
u16 GetGraveCardAndClearGrave2__Replacement(u8 turn)
{
  return GraveyardExpand_PopFixed(turn);
}

LYN_REPLACE_CHECK(GetGraveCardAndClearGrave);
u16 GetGraveCardAndClearGrave__Replacement(u8 turn)
{
  return GraveyardExpand_PopTurn(turn);
}
