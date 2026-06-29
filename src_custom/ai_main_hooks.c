#include "global.h"
#include "common-chax.h"
#include "ai_sim.h"
#include "duel.h"
#include "expanded_graveyard.h"
#include "permanent_effect.h"

void TryActivatingTurnEffects(void);
void TryAttackVoicing(void);
void sub_801B66C(void);
void sub_8040EF0(void);
void UpdateDuelGfxExceptField(void);
void PlayActionSoundEffect(void);
void CheckWinConditionFINAL(void);
void CheckWinConditionExodia(void);

u16 sub_800EF0C__Replacement(void);
void sub_800E0D4__Replacement(void);
void TryAttackVoicing(void);

void AI_Main(void);

LYN_REPLACE_CHECK(AI_Main);
void AI_Main__Replacement(void)
{
  TryActivatingTurnEffects();
  if (IsDuelOver() == TRUE)
    return;
  TryActivatingPermanentEffects();
  if (IsDuelOver() == TRUE)
    return;

  while (IsDuelOver() != TRUE) {
    u16 temp;

    AiSimulateAllCandidateActions();

    temp = sub_800EF0C__Replacement();
    if (temp == 0)
      break;

    AiInitCommandData(temp);
    TryAttackVoicing();
    sub_800E0D4__Replacement();
    if (GraveyardExpand_IsEnabled()) {
      GraveyardExpand_SyncLegacyTop(DUEL_PLAYER);
      GraveyardExpand_SyncLegacyTop(DUEL_OPPONENT);
    }
    if (gUnk2023EA0.unk18) {
      sub_801B66C();
      sub_8040EF0();
    } else {
      UpdateDuelGfxExceptField();
    }
    PlayActionSoundEffect();
    CheckWinConditionFINAL();
    CheckWinConditionExodia();
    TryActivatingPermanentEffects();
  }
}
