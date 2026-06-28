#include "global.h"
#include "common-chax.h"
#include "coffin_seller.h"
#include "call_of_the_haunted.h"
#include "configs/runtime.h"
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
    if (GraveyardExpand_IsEnabled() && !gRuntimeConfig.fast_ai) {
      u8 count = gExpandedGraveyardCount[i];

      gAiSimSavedExpandedGraveyardCount[i] = count;
      for (j = 0; j < count; j++)
        gAiSimSavedExpandedGraveyard[i][j] = gExpandedGraveyard[i][j];
    }
  }
}

LYN_REPLACE_CHECK(sub_800EE94);
void sub_800EE94__Replacement(void)
{
  u8 i;
  u8 j;

  gDuel = gUnk_8DFF6A4->duel;
  for (i = 0; i < 2; i++) {
    u8 count;

    gDuelDecks[i].cardsDrawn = gUnk_8DFF6A4->duelDecks[i].cardsDrawn;
    gDuelLifePoints[i] = gUnk_8DFF6A4->lifePoints[i];
    gDuelistStatus[i] = gUnk_8DFF6A4->duelistStatus[i];
    if (!GraveyardExpand_IsEnabled() || gRuntimeConfig.fast_ai)
      continue;

    count = gAiSimSavedExpandedGraveyardCount[i];
    gExpandedGraveyardCount[i] = count;
    for (j = 0; j < count; j++)
      gExpandedGraveyard[i][j] = gAiSimSavedExpandedGraveyard[i][j];
  }

  gDebugRulesetTurnAttackUsed = gAiSimSavedDebugRulesetTurnAttackUsed;
  gTheDarkDoorTurnAttackUsed = gAiSimSavedTheDarkDoorTurnAttackUsed;
  gAiResimulateAfterCallOfTheHaunted = gAiSimSavedResimulateAfterCallOfTheHaunted;
  gVengefulBogSpiritSummonedMaskOpponentRow = gAiSimSavedVengefulBogSpiritMaskOpponentRow;
  gVengefulBogSpiritSummonedMaskPlayerRow = gAiSimSavedVengefulBogSpiritMaskPlayerRow;
  ClearCoffinSellerPending();
}
