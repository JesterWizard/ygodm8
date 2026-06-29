#include "global.h"
#include "common-chax.h"
#include "coffin_seller.h"
#include "call_of_the_haunted.h"
#include "configs/runtime.h"
#include "dark_magician_of_chaos.h"
#include "debug_ruleset.h"
#include "duel.h"
#include "expanded_graveyard.h"
#include "the_dark_door.h"
#include "vengeful_bog_spirit.h"

struct AiDuelSimulationState {
  struct Duel duel;
  struct DuelDeck duelDecks[2];
  u16 lifePoints[2];
  u8 duelistStatus[2];
};

extern struct AiDuelSimulationState *gUnk_8DFF6A4;
extern u8 gDebugRulesetTurnAttackUsed;
extern u8 gTheDarkDoorTurnAttackUsed;
extern u8 gAiSimSavedDebugRulesetTurnAttackUsed;
extern u8 gAiSimSavedTheDarkDoorTurnAttackUsed;
extern u8 gAiSimSavedResimulateAfterCallOfTheHaunted;
extern u8 gAiSimSavedVengefulBogSpiritMaskOpponentRow;
extern u8 gAiSimSavedVengefulBogSpiritMaskPlayerRow;
extern u16 gExpandedGraveyard[2][EXPANDED_GRAVEYARD_CAPACITY];
extern u8 gExpandedGraveyardCount[2];
extern u16 gAiSimSavedExpandedGraveyard[2][EXPANDED_GRAVEYARD_CAPACITY];
extern u8 gAiSimSavedExpandedGraveyardCount[2];
extern u16 gAiBatchCheckpointGraveyard[2][EXPANDED_GRAVEYARD_CAPACITY];
extern u8 gAiBatchCheckpointGraveyardCount[2];

void AiSimClearSavedGraveyard(void)
{
  u8 duelist;
  u8 i;

  for (duelist = 0; duelist < 2; duelist++) {
    gAiSimSavedExpandedGraveyardCount[duelist] = 0;
    gAiBatchCheckpointGraveyardCount[duelist] = 0;
    for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++) {
      gAiSimSavedExpandedGraveyard[duelist][i] = CARD_NONE;
      gAiBatchCheckpointGraveyard[duelist][i] = CARD_NONE;
    }
  }
}

void AiSimBeginBatchGraveyardCheckpoint(void)
{
  u8 duelist;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return;

  for (duelist = 0; duelist < 2; duelist++) {
    u8 count = gExpandedGraveyardCount[duelist];

    gAiBatchCheckpointGraveyardCount[duelist] = count;
    for (i = 0; i < count; i++)
      gAiBatchCheckpointGraveyard[duelist][i] = gExpandedGraveyard[duelist][i];
    for (i = count; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
      gAiBatchCheckpointGraveyard[duelist][i] = CARD_NONE;
  }
}

void AiSimEndBatchGraveyardCheckpoint(void)
{
  u8 duelist;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return;

  for (duelist = 0; duelist < 2; duelist++) {
    u8 count = gAiBatchCheckpointGraveyardCount[duelist];

    gExpandedGraveyardCount[duelist] = count;
    for (i = 0; i < count; i++)
      gExpandedGraveyard[duelist][i] = gAiBatchCheckpointGraveyard[duelist][i];
    for (i = count; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
      gExpandedGraveyard[duelist][i] = CARD_NONE;
    GraveyardExpand_SyncLegacyTop(duelist);
  }
}

void sub_800EE24(void);
void sub_800EE94(void);

LYN_REPLACE_CHECK(sub_800EE24);
void sub_800EE24__Replacement(void)
{
  u8 i;
  u8 j;

  gAiSimSavedDebugRulesetTurnAttackUsed = gDebugRulesetTurnAttackUsed;
  gAiSimSavedTheDarkDoorTurnAttackUsed = gTheDarkDoorTurnAttackUsed;
  gAiSimSavedResimulateAfterCallOfTheHaunted = gAiResimulateAfterCallOfTheHaunted;
  gAiSimSavedVengefulBogSpiritMaskOpponentRow = gVengefulBogSpiritSummonedMaskOpponentRow;
  gAiSimSavedVengefulBogSpiritMaskPlayerRow = gVengefulBogSpiritSummonedMaskPlayerRow;

  gUnk_8DFF6A4->duel = gDuel;
  for (i = 0; i < 2; i++) {
    gUnk_8DFF6A4->duelDecks[i].cardsDrawn = gDuelDecks[i].cardsDrawn;
    gUnk_8DFF6A4->lifePoints[i] = gDuelLifePoints[i];
    gUnk_8DFF6A4->duelistStatus[i] = gDuelistStatus[i];
    if (GraveyardExpand_IsEnabled()) {
      u8 count = gExpandedGraveyardCount[i];

      gAiSimSavedExpandedGraveyardCount[i] = count;
      for (j = 0; j < count; j++)
        gAiSimSavedExpandedGraveyard[i][j] = gExpandedGraveyard[i][j];
      for (j = count; j < EXPANDED_GRAVEYARD_CAPACITY; j++)
        gAiSimSavedExpandedGraveyard[i][j] = CARD_NONE;

      /* ponytail: expanded stack is authoritative; keep legacy top out of snapshot. */
      if (count == 0)
        gUnk_8DFF6A4->duel.duelistbattleState[i].graveyard = CARD_NONE;
      else
        gUnk_8DFF6A4->duel.duelistbattleState[i].graveyard =
            gExpandedGraveyard[i][count - 1];
    }
  }
}

LYN_REPLACE_CHECK(sub_800EE94);
void sub_800EE94__Replacement(void)
{
  u8 i;
  u8 j;

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < 2; i++) {
      u8 count = gAiSimSavedExpandedGraveyardCount[i];

      gExpandedGraveyardCount[i] = count;
      for (j = 0; j < count; j++)
        gExpandedGraveyard[i][j] = gAiSimSavedExpandedGraveyard[i][j];
      for (j = count; j < EXPANDED_GRAVEYARD_CAPACITY; j++)
        gExpandedGraveyard[i][j] = CARD_NONE;
    }
  }

  gDuel = gUnk_8DFF6A4->duel;
  for (i = 0; i < 2; i++) {
    gDuelDecks[i].cardsDrawn = gUnk_8DFF6A4->duelDecks[i].cardsDrawn;
    gDuelLifePoints[i] = gUnk_8DFF6A4->lifePoints[i];
    gDuelistStatus[i] = gUnk_8DFF6A4->duelistStatus[i];
    if (GraveyardExpand_IsEnabled())
      GraveyardExpand_SyncLegacyTop(i);
  }

  gDebugRulesetTurnAttackUsed = gAiSimSavedDebugRulesetTurnAttackUsed;
  gTheDarkDoorTurnAttackUsed = gAiSimSavedTheDarkDoorTurnAttackUsed;
  gAiResimulateAfterCallOfTheHaunted = gAiSimSavedResimulateAfterCallOfTheHaunted;
  gVengefulBogSpiritSummonedMaskOpponentRow = gAiSimSavedVengefulBogSpiritMaskOpponentRow;
  gVengefulBogSpiritSummonedMaskPlayerRow = gAiSimSavedVengefulBogSpiritMaskPlayerRow;
  ClearCoffinSellerPending();
  ClearDarkMagicianOfChaosPending();

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < 2; i++)
      GraveyardExpand_SyncLegacyTop(i);
  }
}
