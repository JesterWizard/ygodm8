#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "dark_calling.h"
#include "dark_fusion.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

u8 DarkCalling_TreatsSpellAsDarkFusion(u16 spellId)
{
  return spellId == DARK_CALLING;
}

static u8 RecipeIsFiendFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  return Duel_CardHasMonsterType(recipe->result, TYPE_FIEND);
}

/* Dark Calling materials: hand and/or GY only (banished via Miracle Fusion pay). */
static u8 CollectHandAndGraveyardSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 gyCount;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][i];

    if (zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;
    if (count >= maxOut)
      break;

    out[count].zone = zone;
    out[count].gyIndex = FUSION_GY_INDEX_NONE;
    out[count].cardId = zone->id;
    count++;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

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

static void RunPlayerDarkCallingFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  sourceCount = CollectHandAndGraveyardSources(sources, FUSION_MAX_SOURCES);
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

  feasibleCount = FilterFeasibleByExtraDeck(feasibleIndices, feasibleCount);
  if (feasibleCount == 0) {
    if (!gHideEffectText) {
      Duel_ShowCardEffectText(DARK_CALLING, CARD_EFFECT_TEXT_DARK_CALLING_POPUP_1);
      PlayMusic(SFX_FORBIDDEN);
    }
    return;
  }

  Duel_ShowEffectText(DARK_CALLING);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe == NULL)
    return;

  /* Banishes hand/GY materials (Miracle Fusion pay). Treated as Dark Fusion FS. */
  FusionDuel_ExecuteMiracleFusion(recipe, sources, sourceCount, DARK_CALLING, FALSE);
  {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

      if (zone != NULL && zone->id == recipe->result) {
        DarkFusion_MarkSummonedZone(zone);
        break;
      }
    }
  }
}

static void DARK_CALLING_ResolveBody(void)
{
  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    sourceCount = CollectHandAndGraveyardSources(sources, FUSION_MAX_SOURCES);
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

    if (gRuntimeConfig.enable_extra_deck
        && !ExtraDeckHasResult(gFusionRecipes[bestIdx].result)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    FusionDuel_ExecuteMiracleFusion(&gFusionRecipes[bestIdx], sources, sourceCount,
                                    DARK_CALLING, TRUE);
    {
      u8 col;

      for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
        struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

        if (zone != NULL && zone->id == gFusionRecipes[bestIdx].result) {
          DarkFusion_MarkSummonedZone(zone);
          break;
        }
      }
    }
    return;
  }

  RunPlayerDarkCallingFlow();
}

APPEND_TEXT void EffectDARK_CALLING(void)
{
  if (Duel_TryResolveSpellThroughTraps(DARK_CALLING, DARK_CALLING_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DARK_CALLING_SelfCheck(void)
{
  if (!Duel_CardHasMonsterType(SUMMONED_SKULL, TYPE_FIEND))
    while (1)
      ;
  if (Duel_CardHasMonsterType(BLUE_EYES_WHITE_DRAGON, TYPE_FIEND))
    while (1)
      ;
}
#endif
