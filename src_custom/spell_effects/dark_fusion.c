#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "dark_fusion.h"
#include "duel_helpers.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

static u8 sDarkFusionProtectedMaskOpponentRow APPEND_DATA = {0};
static u8 sDarkFusionProtectedMaskPlayerRow APPEND_DATA = {0};

static u8 *ProtectedMaskForMonsterRow(u8 fixedRow)
{
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return &sDarkFusionProtectedMaskOpponentRow;
  if (fixedRow == PLAYER_MONSTER_ROW)
    return &sDarkFusionProtectedMaskPlayerRow;
  return NULL;
}

void DarkFusion_MarkSummonedZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;
  u8 *mask;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  mask = ProtectedMaskForMonsterRow(fixedRow);
  if (mask != NULL && fixedCol < MAX_ZONES_IN_ROW)
    *mask |= (u8)(1 << fixedCol);
}

u8 DarkFusion_IsTargetProtected(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;
  u8 *mask;

  if (zone == NULL || !Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &fixedCol))
    return FALSE;

  mask = ProtectedMaskForMonsterRow(fixedRow);
  if (mask == NULL || fixedCol >= MAX_ZONES_IN_ROW)
    return FALSE;

  return (*mask & (u8)(1 << fixedCol)) != 0;
}

void DarkFusion_ClearOnTurnBoundary(void)
{
  sDarkFusionProtectedMaskOpponentRow = 0;
  sDarkFusionProtectedMaskPlayerRow = 0;
}

static u8 RecipeIsFiendFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  return Duel_CardHasMonsterType(recipe->result, TYPE_FIEND);
}

static void MarkDarkFusionSummonedResult(u16 result)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id == result) {
      DarkFusion_MarkSummonedZone(zone);
      return;
    }
  }
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
  MarkDarkFusionSummonedResult(recipe->result);
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
    MarkDarkFusionSummonedResult(gFusionRecipes[bestIdx].result);
    return;
  }

  RunPlayerDarkFusionFlow();
}
