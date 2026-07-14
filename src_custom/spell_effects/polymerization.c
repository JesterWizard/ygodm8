#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/card_effect_texts.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

static void RunPlayerFusionFlow(u16 spellCardId,
                                void (*execute)(const struct FusionRecipe *,
                                                const struct FusionMaterialSource *, u8, u16, u8),
                                FusionRecipeFilterFn filter)
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
                                                        ARRAY_COUNT(feasibleIndices), filter);
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
        Duel_ShowCardEffectText(POLYMERIZATION, CARD_EFFECT_TEXT_POLYMERIZATION_POPUP_2);
        PlayMusic(SFX_FORBIDDEN);
      }
      return;
    }
  }

  Duel_ShowEffectText(spellCardId);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe != NULL)
    execute(recipe, sources, sourceCount, spellCardId, FALSE);
}

APPEND_TEXT void EffectPolymerization(void)
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

    bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, NULL);
    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    FusionDuel_ExecutePolymerization(&gFusionRecipes[bestIdx], sources, sourceCount,
                                     POLYMERIZATION, TRUE);
    return;
  }

  RunPlayerFusionFlow(POLYMERIZATION, FusionDuel_ExecutePolymerization, NULL);
}
