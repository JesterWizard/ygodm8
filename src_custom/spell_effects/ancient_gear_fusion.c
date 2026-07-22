#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyardDuelist);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 RecipeIsAncientGearFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  SetCardInfo(recipe->result);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return Duel_CardNameContains(recipe->result, sAncientGearName);
}

static u8 IsFieldGolemMonster(u16 cardId)
{
  return cardId == ANCIENT_GEAR_GOLEM || cardId == ANCIENT_GEAR_GOLEM_ULTIMATE_POUND;
}

static u8 ControlsFieldGolem(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];
    u16 cardId;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    cardId = Duel_GetEffectiveCardId(zone);
    if (IsFieldGolemMonster(cardId))
      return TRUE;
  }

  return FALSE;
}

static u8 CollectAncientGearFusionSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = FusionDuel_CollectHandAndFieldSources(out, maxOut);
  struct FusionMaterialSource deckSources[FUSION_MAX_SOURCES];
  u8 deckCount;
  u8 i;

  if (!ControlsFieldGolem() || count >= maxOut)
    return count;

  /* If AGG / Ultimate Pound is on field, Deck monsters may also be materials. */
  deckCount = FusionDuel_CollectDeckSources(deckSources, FUSION_MAX_SOURCES);
  for (i = 0; i < deckCount && count < maxOut; i++) {
    out[count] = deckSources[i];
    count++;
  }

  return count;
}

static u8 ExtraDeckAllowsResult(u16 resultId)
{
  u16 *extra;
  u8 active;
  u8 k;

  if (!gRuntimeConfig.enable_extra_deck)
    return TRUE;

  active = gActiveDeckIndex;
  if (active >= PLAYER_DECK_INDEX_MIN && active <= PLAYER_DECK_INDEX_MAX) {
    switch (active) {
    case 1:
      extra = gPlayerDeck1ExtraDeck;
      break;
    case 2:
      extra = gPlayerDeck2ExtraDeck;
      break;
    case 3:
      extra = gPlayerDeck3ExtraDeck;
      break;
    default:
      extra = gPlayerDeck1ExtraDeck;
      break;
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

    if (!ExtraDeckAllowsResult(result))
      continue;

    feasibleIndices[filteredCount++] = feasibleIndices[i];
  }

  return filteredCount;
}

static u8 SelectedUsesDeckWithoutFieldGolem(const struct FusionMaterialSource *selected,
                                            u8 selectedCount)
{
  u8 i;
  u8 usedDeck = FALSE;
  u8 usedFieldGolem = FALSE;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone == NULL) {
      usedDeck = TRUE;
      continue;
    }

    if (IsFieldGolemMonster(Duel_GetEffectiveCardId(selected[i].zone)))
      usedFieldGolem = TRUE;
  }

  return usedDeck && !usedFieldGolem;
}

static void PayAncientGearFusionMaterials(const struct FusionMaterialSource *selected,
                                          u8 selectedCount)
{
  u8 i;
  u8 milled = FALSE;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone != NULL) {
      ClearZoneAndSendMonToGraveyard(selected[i].zone, ACTIVE_DUELIST);
      continue;
    }

    /* Deck material: gyIndex is deck index from CollectDeckSources, but find by
     * id so removals stay stable if indices shift. */
    {
      u16 cardId = selected[i].cardId;
      s16 deckIndex;

      if (cardId == CARD_NONE)
        continue;

      deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
      if (deckIndex < 0)
        continue;

      if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
        continue;

      GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
      milled = TRUE;
    }
  }

  if (milled)
    Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
}

static void ExecuteAncientGearFusion(const struct FusionRecipe *recipe,
                                     const struct FusionMaterialSource *sources, u8 sourceCount,
                                     u8 showEffectText)
{
  struct FusionMaterialSource selected[FUSION_MAX_MATERIALS];
  u16 materialIds[FUSION_MAX_MATERIALS];
  u8 selectedCount;
  s8 emptyZone;
  u8 i;

  if (recipe == NULL)
    return;

  selectedCount = FusionRecipe_SelectSources(recipe, sources, sourceCount, selected,
                                             FUSION_MAX_MATERIALS);
  if (!FusionRecipe_SelectedCountIsValid(recipe, selectedCount)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  /* Deck materials require AGG / Ultimate Pound as a field material. */
  if (SelectedUsesDeckWithoutFieldGolem(selected, selectedCount)) {
    struct FusionMaterialSource handField[FUSION_MAX_SOURCES];
    u8 handFieldCount = FusionDuel_CollectHandAndFieldSources(handField, FUSION_MAX_SOURCES);

    selectedCount = FusionRecipe_SelectSources(recipe, handField, handFieldCount, selected,
                                               FUSION_MAX_MATERIALS);
    if (!FusionRecipe_SelectedCountIsValid(recipe, selectedCount)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }
  }

  emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (emptyZone < 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (showEffectText) {
    Duel_ShowEffectText(ANCIENT_GEAR_FUSION);
    if (IsDuelOver() == TRUE)
      return;
  }

  PayAncientGearFusionMaterials(selected, selectedCount);
  ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1],
                                 ACTIVE_DUELIST);
  for (i = 0; i < selectedCount && i < FUSION_MAX_MATERIALS; i++)
    materialIds[i] = selected[i].cardId;
  FusionDuel_SpecialSummonResultWithMaterials(recipe->result, selectedCount, materialIds);
}

static void RunPlayerAncientGearFusionFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  sourceCount = CollectAncientGearFusionSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices),
                                                        RecipeIsAncientGearFusion);
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

  Duel_ShowEffectText(ANCIENT_GEAR_FUSION);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe == NULL)
    return;

  ExecuteAncientGearFusion(recipe, sources, sourceCount, FALSE);
}

static void ANCIENT_GEAR_FUSION_ResolveBody(void)
{
  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    sourceCount = CollectAncientGearFusionSources(sources, FUSION_MAX_SOURCES);
    if (sourceCount < 2) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, RecipeIsAncientGearFusion);
    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    if (!ExtraDeckAllowsResult(gFusionRecipes[bestIdx].result)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ExecuteAncientGearFusion(&gFusionRecipes[bestIdx], sources, sourceCount, TRUE);
    return;
  }

  RunPlayerAncientGearFusionFlow();
}

APPEND_TEXT void EffectANCIENT_GEAR_FUSION(void)
{
  if (Duel_TryResolveSpellThroughTraps(ANCIENT_GEAR_FUSION, ANCIENT_GEAR_FUSION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ANCIENT_GEAR_FUSION_SelfCheck(void)
{
  struct FusionRecipe recipe;

  recipe.result = ULTIMATE_ANCIENT_GEAR_GOLEM;
  recipe.material1 = CARD_NONE;
  recipe.material2 = CARD_NONE;
  recipe.material3 = CARD_NONE;
  recipe.material4 = CARD_NONE;
  if (!RecipeIsAncientGearFusion(&recipe))
    while (1)
      ;

  recipe.result = BLUE_EYES_ULTIMATE_DRAGON;
  if (RecipeIsAncientGearFusion(&recipe))
    while (1)
      ;

  if (!IsFieldGolemMonster(ANCIENT_GEAR_GOLEM))
    while (1)
      ;
  if (!IsFieldGolemMonster(ANCIENT_GEAR_GOLEM_ULTIMATE_POUND))
    while (1)
      ;
}
#endif
