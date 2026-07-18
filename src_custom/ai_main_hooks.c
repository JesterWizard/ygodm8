#include "global.h"
#include "common-chax.h"
#include "ai_sim.h"
#include "configs/runtime.h"
#include "duel.h"
#include "elemental_hero_core.h"
#include "elemental_hero_ice_edge.h"
#include "elemental_hero_sunrise.h"
#include "expanded_graveyard.h"
#include "graveyard_effects.h"
#include "permanent_effect.h"
#include "yubel.h"
#include "hamon_lord_of_striking_thunder.h"

void TryActivatingTurnEffects(void);
void TryAttackVoicing(void);
void sub_801B66C(void);
void sub_8040EF0(void);
void UpdateDuelGfxExceptField(void);
void PlayActionSoundEffect(void);
void CheckWinConditionFINAL(void);
void CheckWinConditionExodia(void);

extern u8 gHideEffectText;

u16 sub_800EF0C__Replacement(void);
void sub_800E0D4__Replacement(void);

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
    GraveyardExpand_ClearOpponentAfterSimIfFirstTurn();

    temp = sub_800EF0C__Replacement();
    if (temp == 0)
      break;

    AiInitCommandData(temp);
    TryAttackVoicing();
    sub_800E0D4__Replacement();

    if (GraveyardExpand_IsEnabled()) {
      GraveyardExpand_SyncAllLegacyTops();
      /* ponytail: RefreshDisplay rebuilds GY tiles every action — skip on fast_ai. */
      if (!gRuntimeConfig.fast_ai)
        GraveyardExpand_RefreshDisplay();
    }

    if (gUnk2023EA0.unk18) {
      sub_801B66C();
      sub_8040EF0();
    } else {
      UpdateDuelGfxExceptField();
    }

    FinishGraveyardDrawBattleResolve();
    ResolveElementalHeroCoreBattledEffect();
    ResolveElementalHeroIceEdgeBattleEffect();
    ResolveYubelAttackedReflectEffect();
    ResolveElementalHeroSunriseDestroyEffect();
    ResolveHamonLordOfStrikingThunderBattleEffect();
    PlayActionSoundEffect();
    CheckWinConditionFINAL();
    CheckWinConditionExodia();

    if (gRuntimeConfig.fast_ai) {
      /* Cheap permanent path: hide text => aiSim branch (no double GFX rebuild). */
      gHideEffectText = 1;
      TryActivatingPermanentEffects();
      gHideEffectText = 0;
    } else {
      TryActivatingPermanentEffects();
    }
  }

  ResolveYubelEndPhaseEffectsAtTurnEnd();
}
