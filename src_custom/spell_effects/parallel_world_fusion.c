#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_absolute_zero.h"
#include "fusion_duel.h"
#include "parallel_world_fusion.h"
#include "player_decks.h"
#include "removed_from_play.h"
#include "spell_effects.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);

static u8 sParallelWorldFusionSpecialSummonLock APPEND_DATA = {FALSE};

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

static u8 RecipeIsElementalHeroFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  return Duel_IsElementalHeroCard(recipe->result);
}

/* gyIndex stores RFP index for banished materials (zone always NULL). */
static u8 CollectBanishedMonsterSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 rfpCount;
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return 0;

  rfpCount = RemovedFromPlay_GetCount(fixedDuelist);
  for (i = 0; i < rfpCount; i++) {
    u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);

    if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;
    if (count >= maxOut)
      break;

    out[count].zone = NULL;
    out[count].gyIndex = i;
    out[count].cardId = cardId;
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

static void RemoveBanishedAt(u8 fixedDuelist, u8 index)
{
  RemovedFromPlay_RemoveAt(fixedDuelist, index);
}

static void ReturnCardToDeck(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static void PayBanishedShuffleMaterials(const struct FusionMaterialSource *selected,
                                        u8 selectedCount)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 rfpIndices[FUSION_MAX_MATERIALS];
  u8 rfpCount = 0;
  u8 i;
  u8 g;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].gyIndex != FUSION_GY_INDEX_NONE)
      rfpIndices[rfpCount++] = selected[i].gyIndex;
  }

  /* Remove highest RFP indices first so earlier indices stay stable. */
  while (rfpCount > 0) {
    u8 best = 0;

    for (g = 1; g < rfpCount; g++) {
      if (rfpIndices[g] > rfpIndices[best])
        best = g;
    }

    {
      u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, rfpIndices[best]);

      RemoveBanishedAt(fixedDuelist, rfpIndices[best]);
      ReturnCardToDeck(ACTIVE_DUELIST, cardId);
    }

    rfpIndices[best] = rfpIndices[rfpCount - 1];
    rfpCount--;
  }

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
}

static void ExecuteParallelWorldFusion(const struct FusionRecipe *recipe,
                                       const struct FusionMaterialSource *sources,
                                       u8 sourceCount, u8 showEffectText)
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

  emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (emptyZone < 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (showEffectText) {
    Duel_ShowEffectText(PARALLEL_WORLD_FUSION);
    if (IsDuelOver() == TRUE)
      return;
  }

  ElementalHeroAbsoluteZero_BeginSuppressLeave();
  PayBanishedShuffleMaterials(selected, selectedCount);
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);
  for (i = 0; i < selectedCount && i < FUSION_MAX_MATERIALS; i++)
    materialIds[i] = selected[i].cardId;
  FusionDuel_SpecialSummonResultWithMaterials(recipe->result, selectedCount, materialIds);
  ElementalHeroAbsoluteZero_EndSuppressLeave();
  ParallelWorldFusion_MarkSpecialSummonLock();
  UpdateDuelGfxExceptField();
}

void ParallelWorldFusion_MarkSpecialSummonLock(void)
{
  sParallelWorldFusionSpecialSummonLock = TRUE;
}

void ParallelWorldFusion_ClearOnTurnBoundary(void)
{
  sParallelWorldFusionSpecialSummonLock = FALSE;
}

u8 ParallelWorldFusion_BlocksSpecialSummon(u16 cardId)
{
  (void)cardId;
  return sParallelWorldFusionSpecialSummonLock;
}

static void RunPlayerParallelWorldFusionFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  sourceCount = CollectBanishedMonsterSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices),
                                                        RecipeIsElementalHeroFusion);
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

  Duel_ShowEffectText(PARALLEL_WORLD_FUSION);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe == NULL)
    return;

  ExecuteParallelWorldFusion(recipe, sources, sourceCount, FALSE);
}

static void PARALLEL_WORLD_FUSION_ResolveBody(void)
{
  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    sourceCount = CollectBanishedMonsterSources(sources, FUSION_MAX_SOURCES);
    if (sourceCount < 2) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, RecipeIsElementalHeroFusion);
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

    ExecuteParallelWorldFusion(&gFusionRecipes[bestIdx], sources, sourceCount, TRUE);
    return;
  }

  RunPlayerParallelWorldFusionFlow();
}

APPEND_TEXT void EffectPARALLEL_WORLD_FUSION(void)
{
  if (Duel_TryResolveSpellThroughTraps(PARALLEL_WORLD_FUSION, PARALLEL_WORLD_FUSION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void PARALLEL_WORLD_FUSION_SelfCheck(void)
{
  if (!Duel_IsElementalHeroCard(ELEMENTAL_HERO_ABSOLUTE_ZERO))
    while (1)
      ;
  if (Duel_IsElementalHeroCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
