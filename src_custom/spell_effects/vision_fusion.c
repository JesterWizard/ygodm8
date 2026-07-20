#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_absolute_zero.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);

static const char sHeroArchetypeName[] APPEND_RODATA = "HERO";

/* ponytail: OPT flag never clears without a turn-end hook outside this file.
 * Ceiling: once per duel after first activation; upgrade: turn_effect_hooks
 * End Phase / turn-start → sVisionFusionUsedThisTurn = 0. */
static u8 sVisionFusionUsedThisTurn APPEND_DATA = {0};

static u8 RecipeIsHeroFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  SetCardInfo(recipe->result);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return Duel_CardNameContains(recipe->result, sHeroArchetypeName);
}

static u8 ZoneIsActiveBackrow(struct DuelCard *zone)
{
  u8 i;

  if (zone == NULL)
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[ACTIVE_DUELIST_BACKROW][i] == zone)
      return TRUE;
  }

  return FALSE;
}

/* Hand + field monsters, plus up to 2 ST-zone monsters (Continuous Trap Vision HEROs). */
static u8 CollectVisionFusionSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = FusionDuel_CollectHandAndFieldSources(out, maxOut);
  u8 stCount = 0;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW && count < maxOut && stCount < 2; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    out[count].zone = zone;
    out[count].gyIndex = FUSION_GY_INDEX_NONE;
    out[count].cardId = zone->id;
    count++;
    stCount++;
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

/* Hand/field → GY; ST Continuous Trap monsters → banish. */
static void PayVisionFusionMaterials(const struct FusionMaterialSource *selected,
                                     u8 selectedCount)
{
  u8 i;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone == NULL)
      continue;

    if (ZoneIsActiveBackrow(selected[i].zone))
      Duel_BanishZone(selected[i].zone, FALSE);
    else
      ClearZoneAndSendMonToGraveyard(selected[i].zone, ACTIVE_DUELIST);
  }
}

static void ExecuteVisionFusion(const struct FusionRecipe *recipe,
                                const struct FusionMaterialSource *sources,
                                u8 sourceCount, u8 showEffectText)
{
  struct FusionMaterialSource selected[FUSION_MAX_MATERIALS];
  u8 selectedCount;
  s8 emptyZone;

  if (recipe == NULL)
    return;

  selectedCount = FusionRecipe_SelectSources(recipe, sources, sourceCount, selected,
                                             FUSION_MAX_MATERIALS);
  if (!FusionRecipe_SelectedCountIsValid(recipe, selectedCount)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (emptyZone < 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (showEffectText) {
    Duel_ShowEffectText(VISION_FUSION);
    if (IsDuelOver() == TRUE)
      return;
  }

  ElementalHeroAbsoluteZero_BeginSuppressLeave();
  PayVisionFusionMaterials(selected, selectedCount);
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);
  FusionDuel_SpecialSummonResult(recipe->result, selectedCount);
  ElementalHeroAbsoluteZero_EndSuppressLeave();
  UpdateDuelGfxExceptField();

  sVisionFusionUsedThisTurn = TRUE;
}

static void RunPlayerVisionFusionFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  if (sVisionFusionUsedThisTurn) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  sourceCount = CollectVisionFusionSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices),
                                                        RecipeIsHeroFusion);
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = FilterFeasibleByExtraDeck(feasibleIndices, feasibleCount);
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(VISION_FUSION);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe == NULL)
    return;

  ExecuteVisionFusion(recipe, sources, sourceCount, FALSE);
}

static void VISION_FUSION_ResolveBody(void)
{
  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    if (sVisionFusionUsedThisTurn) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    sourceCount = CollectVisionFusionSources(sources, FUSION_MAX_SOURCES);
    if (sourceCount < 2) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, RecipeIsHeroFusion);
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

    ExecuteVisionFusion(&gFusionRecipes[bestIdx], sources, sourceCount, TRUE);
    return;
  }

  RunPlayerVisionFusionFlow();
}

APPEND_TEXT void EffectVISION_FUSION(void)
{
  if (sVisionFusionUsedThisTurn) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(VISION_FUSION, VISION_FUSION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void VISION_FUSION_SelfCheck(void)
{
  struct FusionRecipe heroRecipe;

  heroRecipe.result = ELEMENTAL_HERO_FLAME_WINGMAN;
  heroRecipe.material1 = ELEMENTAL_HERO_AVIAN;
  heroRecipe.material2 = ELEMENTAL_HERO_BURSTINATRIX;
  heroRecipe.material3 = 0;
  heroRecipe.material4 = 0;

  if (!RecipeIsHeroFusion(&heroRecipe))
    while (1)
      ;

  heroRecipe.result = BLUE_EYES_WHITE_DRAGON;
  if (RecipeIsHeroFusion(&heroRecipe))
    while (1)
      ;
}
#endif
