#include "global.h"
#include "common-chax.h"
#include "ai_sim.h"
#include "coffin_seller.h"
#include "call_of_the_haunted.h"
#include "dark_magician_of_chaos.h"
#include "debug_ruleset.h"
#include "duel.h"
#include "expanded_graveyard.h"
#include "the_dark_door.h"
#include "the_wicked_avatar.h"
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
extern u8 gAmebaPendingCount;
extern u8 gAmebaPendingDamageTarget0;
extern u8 gAmebaPendingDamageTarget1;
extern u8 gAiSimSavedAmebaPendingCount;
extern u8 gAiSimSavedAmebaPendingDamageTarget0;
extern u8 gAiSimSavedAmebaPendingDamageTarget1;
extern u8 gAiSimSavedTheWickedAvatarLockFixedDuelist;
extern u8 gAiSimSavedTheWickedAvatarLockTurnsRemaining;

/* ponytail: AI_Data.filler1A8[0..0x13F] — not ram_map; per-candidate + batch GY snapshots. */
#define AI_SIM_GY_CANDIDATE_SNAPSHOT_OFF 0x1A8
#define AI_SIM_GY_BATCH_SNAPSHOT_OFF      0x248

static u16 *AiSimCandidateGraveyardSnapshot(void)
{
  return (u16 *)((u8 *)gUnk_8DFF6A4 + AI_SIM_GY_CANDIDATE_SNAPSHOT_OFF);
}

static u16 *AiSimBatchGraveyardSnapshot(void)
{
  return (u16 *)((u8 *)gUnk_8DFF6A4 + AI_SIM_GY_BATCH_SNAPSHOT_OFF);
}

void AiSimBatchGraveyardSave(void)
{
  if (!GraveyardExpand_IsEnabled())
    return;

  GraveyardExpand_CopyStacks(AiSimBatchGraveyardSnapshot());
}

void AiSimBatchGraveyardRestore(void)
{
  if (!GraveyardExpand_IsEnabled())
    return;

  GraveyardExpand_LoadStacks(AiSimBatchGraveyardSnapshot());
  GraveyardExpand_SyncAllLegacyTops();
  GraveyardExpand_RefreshDisplay();
}

void sub_800EE24(void);
void sub_800EE94(void);

LYN_REPLACE_CHECK(sub_800EE24);
void sub_800EE24__Replacement(void)
{
  u8 i;

  if (GraveyardExpand_IsEnabled())
    GraveyardExpand_CopyStacks(AiSimCandidateGraveyardSnapshot());

  gAiSimSavedDebugRulesetTurnAttackUsed = gDebugRulesetTurnAttackUsed;
  gAiSimSavedTheDarkDoorTurnAttackUsed = gTheDarkDoorTurnAttackUsed;
  gAiSimSavedResimulateAfterCallOfTheHaunted = gAiResimulateAfterCallOfTheHaunted;
  gAiSimSavedVengefulBogSpiritMaskOpponentRow = gVengefulBogSpiritSummonedMaskOpponentRow;
  gAiSimSavedVengefulBogSpiritMaskPlayerRow = gVengefulBogSpiritSummonedMaskPlayerRow;
  gAiSimSavedAmebaPendingCount = gAmebaPendingCount;
  gAiSimSavedAmebaPendingDamageTarget0 = gAmebaPendingDamageTarget0;
  gAiSimSavedAmebaPendingDamageTarget1 = gAmebaPendingDamageTarget1;
  gAiSimSavedTheWickedAvatarLockFixedDuelist = gTheWickedAvatarLockFixedDuelist;
  gAiSimSavedTheWickedAvatarLockTurnsRemaining = gTheWickedAvatarLockTurnsRemaining;

  gUnk_8DFF6A4->duel = gDuel;
  for (i = 0; i < 2; i++) {
    gUnk_8DFF6A4->duelDecks[i].cardsDrawn = gDuelDecks[i].cardsDrawn;
    gUnk_8DFF6A4->lifePoints[i] = gDuelLifePoints[i];
    gUnk_8DFF6A4->duelistStatus[i] = gDuelistStatus[i];
    if (GraveyardExpand_IsEnabled()) {
      u8 count = GraveyardExpand_GetCount(i);

      /* ponytail: expanded stack is authoritative; keep legacy top out of snapshot. */
      if (count == 0)
        gUnk_8DFF6A4->duel.duelistbattleState[i].graveyard = CARD_NONE;
      else
        gUnk_8DFF6A4->duel.duelistbattleState[i].graveyard =
            GraveyardExpand_GetCardAt(i, count - 1);
    }
  }
}

LYN_REPLACE_CHECK(sub_800EE94);
void sub_800EE94__Replacement(void)
{
  u8 i;

  if (GraveyardExpand_IsEnabled())
    GraveyardExpand_LoadStacks(AiSimCandidateGraveyardSnapshot());

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
  gAmebaPendingCount = gAiSimSavedAmebaPendingCount;
  gAmebaPendingDamageTarget0 = gAiSimSavedAmebaPendingDamageTarget0;
  gAmebaPendingDamageTarget1 = gAiSimSavedAmebaPendingDamageTarget1;
  gTheWickedAvatarLockFixedDuelist = gAiSimSavedTheWickedAvatarLockFixedDuelist;
  gTheWickedAvatarLockTurnsRemaining = gAiSimSavedTheWickedAvatarLockTurnsRemaining;
  ClearCoffinSellerPending();
  ClearDarkMagicianOfChaosPending();
}
