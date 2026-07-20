#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_economics.h"
#include "spell_effects.h"

#define ULTRA_POLYMERIZATION_LP_COST 2000

static u8 RecipeIsTwoMaterialFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  return FusionRecipe_MaterialCount(recipe) == 2;
}

static u8 CollectFieldMonsterSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;
    if (count >= maxOut)
      break;

    out[count].zone = zone;
    out[count].gyIndex = FUSION_GY_INDEX_NONE;
    out[count].cardId = zone->id;
    count++;
  }

  return count;
}

static u8 ExtraDeckHasResult(u16 resultId)
{
  u16 *extra;
  u8 active;
  u8 k;

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

  for (k = 0; k < EXTRA_DECK_SIZE; k++) {
    if (extra[k] == resultId)
      return TRUE;
  }

  return FALSE;
}

static u8 FilterFeasibleByExtraDeck(u8 *feasibleIndices, u8 feasibleCount)
{
  u8 i;
  u8 filteredCount = 0;

  if (!gRuntimeConfig.enable_extra_deck)
    return feasibleCount;

  for (i = 0; i < feasibleCount; i++) {
    u16 result = gFusionRecipes[feasibleIndices[i]].result;

    if (!ExtraDeckHasResult(result))
      continue;

    feasibleIndices[filteredCount++] = feasibleIndices[i];
  }

  return filteredCount;
}

static u8 CanPayUltraPolymerizationCost(void)
{
  if (IsSpellEconomicsActiveForActiveDuelist())
    return TRUE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= ULTRA_POLYMERIZATION_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= ULTRA_POLYMERIZATION_LP_COST;
}

static u8 CanActivateUltraPolymerization(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;

  if (!CanPayUltraPolymerizationCost())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  sourceCount = CollectFieldMonsterSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2)
    return FALSE;

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices),
                                                        RecipeIsTwoMaterialFusion);
  if (feasibleCount == 0)
    return FALSE;

  feasibleCount = FilterFeasibleByExtraDeck(feasibleIndices, feasibleCount);
  return feasibleCount > 0;
}

static void RunPlayerUltraPolymerizationFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  if (!CanActivateUltraPolymerization()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  sourceCount = CollectFieldMonsterSources(sources, FUSION_MAX_SOURCES);
  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices),
                                                        RecipeIsTwoMaterialFusion);
  feasibleCount = FilterFeasibleByExtraDeck(feasibleIndices, feasibleCount);
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (!IsSpellEconomicsActiveForActiveDuelist()) {
    if (Duel_ChangeLp(ACTIVE_DUELIST, -ULTRA_POLYMERIZATION_LP_COST, FALSE)
        == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_ShowEffectText(ULTRA_POLYMERIZATION);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe == NULL)
    return;

  FusionDuel_ExecutePolymerization(recipe, sources, sourceCount, ULTRA_POLYMERIZATION, FALSE);

  /* ponytail: "neither player can activate cards/effects in response" needs a
   * response-lock flag outside this file (trap/chain gate). Ceiling: LP pay +
   * field-only 2-material Fusion; upgrade: set no-response flag around
   * Duel_TryResolveSpellThroughTrapsEx / activation. */

  /* ponytail: GY ignition "banish this card, target 1 Fusion Summoned by this
   * card; SS all materials used from GY, ATK/DEF 0, effects negated" needs GY
   * activation + material-memory outside this file.
   * Ceiling: on-field Fusion only; upgrade: store material ids on summon tag →
   * GY activate ULTRA_POLYMERIZATION → Duel_BanishGraveyard → SS materials with
   * ATK/DEF 0 + negate. */
}

static void ULTRA_POLYMERIZATION_ResolveBody(void)
{
  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    if (!CanActivateUltraPolymerization()) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    sourceCount = CollectFieldMonsterSources(sources, FUSION_MAX_SOURCES);
    bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, RecipeIsTwoMaterialFusion);
    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    if (gRuntimeConfig.enable_extra_deck
        && !ExtraDeckHasResult(gFusionRecipes[bestIdx].result)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    if (!IsSpellEconomicsActiveForActiveDuelist()) {
      if (Duel_ChangeLp(ACTIVE_DUELIST, -ULTRA_POLYMERIZATION_LP_COST, FALSE)
          == DUEL_ACTION_DUEL_OVER)
        return;
    }

    FusionDuel_ExecutePolymerization(&gFusionRecipes[bestIdx], sources, sourceCount,
                                     ULTRA_POLYMERIZATION, TRUE);
    return;
  }

  RunPlayerUltraPolymerizationFlow();
}

APPEND_TEXT void EffectULTRA_POLYMERIZATION(void)
{
  if (!CanActivateUltraPolymerization()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTrapsEx(ULTRA_POLYMERIZATION, ULTRA_POLYMERIZATION_LP_COST,
                                         ULTRA_POLYMERIZATION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ULTRA_POLYMERIZATION_SelfCheck(void)
{
  const struct FusionRecipe *twoMat = FusionRecipe_FindByResult(ELEMENTAL_HERO_FLAME_WINGMAN);

  if (twoMat == NULL || !RecipeIsTwoMaterialFusion(twoMat))
    while (1)
      ;
  if (RecipeIsTwoMaterialFusion(NULL))
    while (1)
      ;
}
#endif
