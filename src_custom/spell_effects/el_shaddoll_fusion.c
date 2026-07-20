#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

static const char sShaddollArchetypeName[] APPEND_RODATA = "Shaddoll";

static u8 RecipeIsShaddollFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  SetCardInfo(recipe->result);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return Duel_CardNameContains(recipe->result, sShaddollArchetypeName);
}

static void RunPlayerElShaddollFusionFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  sourceCount = FusionDuel_CollectFusionSpellSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices),
                                                        RecipeIsShaddollFusion);
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (gRuntimeConfig.enable_extra_deck) {
    u16 *extra;
    u8 active;
    u8 i, filteredCount;

    active = gActiveDeckIndex;
    if (active >= PLAYER_DECK_INDEX_MIN && active <= PLAYER_DECK_INDEX_MAX) {
      switch (active) {
      case 1: extra = gPlayerDeck1ExtraDeck; break;
      case 2: extra = gPlayerDeck2ExtraDeck; break;
      case 3: extra = gPlayerDeck3ExtraDeck; break;
      default: extra = gPlayerDeck1ExtraDeck; break;
      }
    } else {
      extra = gPlayerDeck1ExtraDeck;
    }

    filteredCount = 0;
    for (i = 0; i < feasibleCount; i++) {
      u16 result = gFusionRecipes[feasibleIndices[i]].result;
      u8 k;

      for (k = 0; k < EXTRA_DECK_SIZE; k++) {
        if (extra[k] == result) {
          filteredCount++;
          break;
        }
      }
    }

    if (filteredCount == 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }
  }

  Duel_ShowEffectText(EL_SHADDOLL_FUSION);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe != NULL)
    FusionDuel_ExecutePolymerization(recipe, sources, sourceCount, EL_SHADDOLL_FUSION, FALSE);
}

APPEND_TEXT void EffectEL_SHADDOLL_FUSION(void)
{
  /* ponytail: once-per-turn activation not tracked (no BSS turn flag editable
   * from this file alone). Ceiling: multiple El Shaddoll Fusion per turn possible;
   * upgrade: shared OPT RAM bit / effect_usage once_per_turn. */

  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    sourceCount = FusionDuel_CollectFusionSpellSources(sources, FUSION_MAX_SOURCES);
    if (sourceCount < 2) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, RecipeIsShaddollFusion);
    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    FusionDuel_ExecutePolymerization(&gFusionRecipes[bestIdx], sources, sourceCount,
                                     EL_SHADDOLL_FUSION, TRUE);
    return;
  }

  RunPlayerElShaddollFusionFlow();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElShaddollFusion_SelfCheck(void)
{
  struct FusionRecipe recipe;

  recipe.result = EL_SHADDOLL_CONSTRUCT;
  recipe.material1 = CARD_NONE;
  recipe.material2 = CARD_NONE;
  recipe.material3 = CARD_NONE;
  recipe.material4 = CARD_NONE;
  if (!RecipeIsShaddollFusion(&recipe))
    while (1)
      ;

  recipe.result = BLUE_EYES_WHITE_DRAGON;
  if (RecipeIsShaddollFusion(&recipe))
    while (1)
      ;
}
#endif
