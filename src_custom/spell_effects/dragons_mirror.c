#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "fusion_duel.h"
#include "spell_effects.h"

static u8 RecipeIsDragonFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  return Duel_CardHasMonsterType(recipe->result, TYPE_DRAGON);
}

static void RunPlayerDragonsMirrorFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  sourceCount = FusionDuel_CollectFieldAndGraveyardSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices),
                                                        RecipeIsDragonFusion);
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(DRAGONS_MIRROR);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe != NULL)
    FusionDuel_ExecuteMiracleFusion(recipe, sources, sourceCount, DRAGONS_MIRROR, FALSE);
}

static void DRAGONS_MIRROR_ResolveBody(void)
{
  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    sourceCount = FusionDuel_CollectFieldAndGraveyardSources(sources, FUSION_MAX_SOURCES);
    if (sourceCount < 2) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, RecipeIsDragonFusion);
    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    FusionDuel_ExecuteMiracleFusion(&gFusionRecipes[bestIdx], sources, sourceCount, DRAGONS_MIRROR,
                                    TRUE);
    return;
  }

  RunPlayerDragonsMirrorFlow();
}

APPEND_TEXT void EffectDRAGONS_MIRROR(void)
{
  if (Duel_TryResolveSpellThroughTraps(DRAGONS_MIRROR, DRAGONS_MIRROR_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DRAGONS_MIRROR_SelfCheck(void)
{
  if (!Duel_CardHasMonsterType(BLUE_EYES_WHITE_DRAGON, TYPE_DRAGON))
    while (1)
      ;
  if (Duel_CardHasMonsterType(DARK_MAGICIAN, TYPE_DRAGON))
    while (1)
      ;
}
#endif
