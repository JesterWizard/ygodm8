#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

static u8 RecipeIsFiendFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  return Duel_CardHasMonsterType(recipe->result, TYPE_FIEND);
}

static void RunPlayerDarkFusionFlow(void)
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
                                                        RecipeIsFiendFusion);
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
      if (!gHideEffectText) {
        Duel_ShowCardEffectText(DARK_FUSION, CARD_EFFECT_TEXT_DARK_FUSION_POPUP_1);
        PlayMusic(SFX_FORBIDDEN);
      }
      return;
    }
  }

  Duel_ShowEffectText(DARK_FUSION);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe == NULL)
    return;

  FusionDuel_ExecutePolymerization(recipe, sources, sourceCount, DARK_FUSION, FALSE);

  /* ponytail: "opponent cannot target the Fusion this turn" needs a turn-scoped
   * targeting-protect flag on the summoned zone (no in-file targeting gate).
   * Ceiling: Fiend Fusion via Poly materials only; upgrade: mark result zone
   * + spell/trap/monster target validators skip it until turn end. */
}

APPEND_TEXT void EffectDARK_FUSION(void)
{
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

    bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, RecipeIsFiendFusion);
    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    FusionDuel_ExecutePolymerization(&gFusionRecipes[bestIdx], sources, sourceCount,
                                     DARK_FUSION, TRUE);

    /* ponytail: targeting protect this turn — same ceiling as player path. */
    return;
  }

  RunPlayerDarkFusionFlow();
}
