#include "global.h"
#include "ai_sim.h"
#include "configs/runtime.h"
#include "duel.h"
#include "expanded_graveyard.h"

extern u16 gExpandedGraveyard[2][EXPANDED_GRAVEYARD_CAPACITY];
extern u8 gExpandedGraveyardCount[2];

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

static void SyncLegacyTop(u8 fixedDuelist)
{
  u8 count;

  count = gExpandedGraveyardCount[fixedDuelist];
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
    gExpandedGraveyardCount[duelist] = 0;
    for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
      gExpandedGraveyard[duelist][i] = CARD_NONE;
  }
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
    gDuel.duelistbattleState[fixedDuelist].graveyard = cardId;
    return;
  }

  count = gExpandedGraveyardCount[fixedDuelist];
  if (count >= EXPANDED_GRAVEYARD_CAPACITY) {
    /* ponytail: 40-card cap matches deck size; on overflow, drop oldest. */
    for (i = 1; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
      gExpandedGraveyard[fixedDuelist][i - 1] = gExpandedGraveyard[fixedDuelist][i];
    count = EXPANDED_GRAVEYARD_CAPACITY - 1;
  }

  gExpandedGraveyard[fixedDuelist][count] = cardId;
  gExpandedGraveyardCount[fixedDuelist] = count + 1;
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

  if (gAiSimInBatch)
    return CARD_NONE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    return cardId;
  }

  count = gExpandedGraveyardCount[fixedDuelist];
  if (count == 0)
    return CARD_NONE;

  count--;
  cardId = gExpandedGraveyard[fixedDuelist][count];
  gExpandedGraveyard[fixedDuelist][count] = CARD_NONE;
  gExpandedGraveyardCount[fixedDuelist] = count;
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
  return gExpandedGraveyardCount[fixedDuelist];
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

  if (gAiSimInBatch)
    return CARD_NONE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    return cardId;
  }

  count = gExpandedGraveyardCount[fixedDuelist];
  if (index >= count)
    return CARD_NONE;

  cardId = gExpandedGraveyard[fixedDuelist][index];
  for (i = index; i + 1 < count; i++)
    gExpandedGraveyard[fixedDuelist][i] = gExpandedGraveyard[fixedDuelist][i + 1];
  gExpandedGraveyard[fixedDuelist][count - 1] = CARD_NONE;
  gExpandedGraveyardCount[fixedDuelist] = count - 1;
  SyncLegacyTop(fixedDuelist);
  return cardId;
}

u16 GraveyardExpand_RemoveAtTurn(u8 turnDuelist, u8 index)
{
  return GraveyardExpand_RemoveAtFixed(TurnDuelistToFixed(turnDuelist), index);
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
