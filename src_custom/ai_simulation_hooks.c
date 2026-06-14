#include "global.h"
#include "common-chax.h"
#include "coffin_seller.h"
#include "call_of_the_haunted.h"
#include "debug_ruleset.h"
#include "duel.h"
#include "the_dark_door.h"

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

void sub_800EE24(void);
void sub_800EE94(void);

LYN_REPLACE_CHECK(sub_800EE24);
void sub_800EE24__Replacement(void)
{
  u8 i;

  gAiSimSavedDebugRulesetTurnAttackUsed = gDebugRulesetTurnAttackUsed;
  gAiSimSavedTheDarkDoorTurnAttackUsed = gTheDarkDoorTurnAttackUsed;
  gAiSimSavedResimulateAfterCallOfTheHaunted = gAiResimulateAfterCallOfTheHaunted;

  gUnk_8DFF6A4->duel = gDuel;
  for (i = 0; i < 2; i++) {
    gUnk_8DFF6A4->duelDecks[i].cardsDrawn = gDuelDecks[i].cardsDrawn;
    gUnk_8DFF6A4->lifePoints[i] = gDuelLifePoints[i];
    gUnk_8DFF6A4->duelistStatus[i] = gDuelistStatus[i];
  }
}

LYN_REPLACE_CHECK(sub_800EE94);
void sub_800EE94__Replacement(void)
{
  u8 i;

  gDuel = gUnk_8DFF6A4->duel;
  for (i = 0; i < 2; i++) {
    gDuelDecks[i].cardsDrawn = gUnk_8DFF6A4->duelDecks[i].cardsDrawn;
    gDuelLifePoints[i] = gUnk_8DFF6A4->lifePoints[i];
    gDuelistStatus[i] = gUnk_8DFF6A4->duelistStatus[i];
  }

  gDebugRulesetTurnAttackUsed = gAiSimSavedDebugRulesetTurnAttackUsed;
  gTheDarkDoorTurnAttackUsed = gAiSimSavedTheDarkDoorTurnAttackUsed;
  gAiResimulateAfterCallOfTheHaunted = gAiSimSavedResimulateAfterCallOfTheHaunted;
  ClearCoffinSellerPending();
}
