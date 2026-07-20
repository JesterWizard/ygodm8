#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_absolute_zero.h"
#include "expanded_graveyard.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);

static const char sShaddollArchetypeName[] APPEND_RODATA = "Shaddoll";

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

static u8 RecipeIsShaddollFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  SetCardInfo(recipe->result);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return Duel_CardNameContains(recipe->result, sShaddollArchetypeName);
}

static u8 IsExtraDeckMonsterId(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == FUSION_CARD || gCardInfo.color == SYNCHRO_CARD
         || gCardInfo.color == XYZ_CARD || gCardInfo.color == LINK_CARD;
}

/* Proxy for "Special Summoned from the Extra Deck" — Extra Deck colors on field. */
static u8 OpponentControlsExtraDeckMonster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone != NULL && IsExtraDeckMonsterId(zone->id))
      return TRUE;
  }

  return FALSE;
}

static u8 CollectShaddollSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = FusionDuel_CollectHandAndFieldSources(out, maxOut);
  struct FusionMaterialSource deck[FUSION_MAX_SOURCES];
  u8 deckCount;
  u8 i;

  if (!OpponentControlsExtraDeckMonster() || count >= maxOut)
    return count;

  deckCount = FusionDuel_CollectDeckSources(deck, FUSION_MAX_SOURCES);
  for (i = 0; i < deckCount && count < maxOut; i++) {
    out[count] = deck[i];
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

static u8 ExtraDeckAllowsFeasible(const u8 *feasibleIndices, u8 feasibleCount)
{
  u8 i;

  if (!gRuntimeConfig.enable_extra_deck)
    return TRUE;

  for (i = 0; i < feasibleCount; i++) {
    if (ExtraDeckHasResult(gFusionRecipes[feasibleIndices[i]].result))
      return TRUE;
  }

  return FALSE;
}

/* Pay hand/field to GY; deck indices use FusionMaterialSource.gyIndex. */
static void PayShaddollFusionMaterials(const struct FusionMaterialSource *selected,
                                       u8 selectedCount)
{
  u8 deckIndices[FUSION_MAX_MATERIALS];
  u8 deckCount = 0;
  u8 i;
  u8 d;
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone != NULL)
      ClearZoneAndSendMonToGraveyard(selected[i].zone, ACTIVE_DUELIST);
    else if (selected[i].gyIndex != FUSION_GY_INDEX_NONE)
      deckIndices[deckCount++] = selected[i].gyIndex;
  }

  while (deckCount > 0) {
    u8 best = 0;
    u8 deckIndex;
    u16 cardId;

    for (d = 1; d < deckCount; d++) {
      if (deckIndices[d] > deckIndices[best])
        best = d;
    }

    deckIndex = deckIndices[best];
    if (deckIndex >= gDuelDecks[fixedDuelist].cardsDrawn
        && deckIndex < NumCardsInDeck(fixedDuelist)) {
      cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
      if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndex, FALSE) == DUEL_ACTION_OK)
        GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
    }

    deckIndices[best] = deckIndices[deckCount - 1];
    deckCount--;
  }

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
}

static void ExecuteShaddollFusion(const struct FusionRecipe *recipe,
                                  const struct FusionMaterialSource *sources,
                                  u8 sourceCount, u16 spellCardId, u8 showEffectText)
{
  struct FusionMaterialSource selected[FUSION_MAX_MATERIALS];
  u8 selectedCount;
  s8 emptyZone;

  if (recipe == NULL)
    return;

  selectedCount = FusionRecipe_SelectSources(recipe, sources, sourceCount, selected,
                                             FUSION_MAX_MATERIALS);
  if (!FusionRecipe_SelectedCountIsValid(recipe, selectedCount))
    return;

  emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (emptyZone < 0)
    return;

  if (showEffectText) {
    Duel_ShowEffectText(spellCardId);
    if (IsDuelOver() == TRUE)
      return;
  }

  ElementalHeroAbsoluteZero_BeginSuppressLeave();
  PayShaddollFusionMaterials(selected, selectedCount);
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);
  FusionDuel_SpecialSummonResult(recipe->result, selectedCount);
  ElementalHeroAbsoluteZero_EndSuppressLeave();
  UpdateDuelGfxExceptField();
}

static void RunPlayerShaddollFusionFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  sourceCount = CollectShaddollSources(sources, FUSION_MAX_SOURCES);
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

  if (!ExtraDeckAllowsFeasible(feasibleIndices, feasibleCount)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(SHADDOLL_FUSION);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe != NULL)
    ExecuteShaddollFusion(recipe, sources, sourceCount, SHADDOLL_FUSION, FALSE);
}

static void SHADDOLL_FUSION_ResolveBody(void)
{
  /* ponytail: once-per-turn activation not tracked (no BSS turn flag editable
   * from this file alone). Ceiling: multiple Shaddoll Fusion per turn possible;
   * upgrade: shared OPT RAM bit / effect_usage once_per_turn. */

  /* ponytail: Extra Deck SS detection uses Fusion/Synchro/Xyz/Link color on
   * opponent's field (no per-zone summon-origin flag). Ceiling: misses Main Deck
   * monsters SS'd from Extra edge cases; upgrade: mark Extra Deck origin on SS. */

  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    sourceCount = CollectShaddollSources(sources, FUSION_MAX_SOURCES);
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

    if (gRuntimeConfig.enable_extra_deck
        && !ExtraDeckHasResult(gFusionRecipes[bestIdx].result)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ExecuteShaddollFusion(&gFusionRecipes[bestIdx], sources, sourceCount, SHADDOLL_FUSION,
                          TRUE);
    return;
  }

  RunPlayerShaddollFusionFlow();
}

APPEND_TEXT void EffectSHADDOLL_FUSION(void)
{
  if (Duel_TryResolveSpellThroughTraps(SHADDOLL_FUSION, SHADDOLL_FUSION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void SHADDOLL_FUSION_SelfCheck(void)
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
