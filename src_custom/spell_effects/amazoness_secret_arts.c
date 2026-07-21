#include "global.h"
#include "common-chax.h"
#include "amazoness_secret_arts.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern u8 gAmazonessSecretArtsExtraMaterial;

/* Field OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */

static u8 RecipeIsAmazonessFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  SetCardInfo(recipe->result);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return Duel_IsAmazonessCard(recipe->result);
}

static u16 *ActiveExtraDeck(void)
{
  u8 active = gActiveDeckIndex;

  if (active >= PLAYER_DECK_INDEX_MIN && active <= PLAYER_DECK_INDEX_MAX) {
    switch (active) {
    case 1: return gPlayerDeck1ExtraDeck;
    case 2: return gPlayerDeck2ExtraDeck;
    case 3: return gPlayerDeck3ExtraDeck;
    default: return gPlayerDeck1ExtraDeck;
    }
  }

  return gPlayerDeck1ExtraDeck;
}

static u8 ExtraDeckHasResult(u16 resultId)
{
  u16 *extra = ActiveExtraDeck();
  u8 k;

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

static u8 ExtraDeckHasAmazonessMonster(void)
{
  u16 *extra = ActiveExtraDeck();
  u8 k;

  if (!gRuntimeConfig.enable_extra_deck)
    return FALSE;

  for (k = 0; k < EXTRA_DECK_SIZE; k++) {
    u16 cardId = extra[k];

    if (cardId != CARD_NONE && Duel_IsAmazonessCard(cardId)
        && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER)
      return TRUE;
  }

  return FALSE;
}

u8 AmazonessSecretArts_ExtraMaterialActive(void)
{
  return gAmazonessSecretArtsExtraMaterial != 0;
}

void AmazonessSecretArts_ClearExtraMaterial(void)
{
  gAmazonessSecretArtsExtraMaterial = 0;
}

static void ActivateExtraMaterialForTurn(void)
{
  gAmazonessSecretArtsExtraMaterial = 1;
}

u8 AmazonessSecretArts_IsExtraDeckSource(const struct FusionMaterialSource *src)
{
  if (src == NULL || src->zone != NULL)
    return FALSE;

  return src->gyIndex >= FUSION_EXTRA_SLOT_BASE
      && (src->gyIndex - FUSION_EXTRA_SLOT_BASE) < EXTRA_DECK_SIZE;
}

u8 AmazonessSecretArts_AppendExtraDeckSources(struct FusionMaterialSource *out, u8 count,
                                              u8 maxOut)
{
  u16 *extra;
  u8 k;

  if (!AmazonessSecretArts_ExtraMaterialActive() || out == NULL)
    return count;

  if (!gRuntimeConfig.enable_extra_deck)
    return count;

  extra = ActiveExtraDeck();
  for (k = 0; k < EXTRA_DECK_SIZE && count < maxOut; k++) {
    u16 cardId = extra[k];

    if (cardId == CARD_NONE)
      continue;
    if (!Duel_IsAmazonessCard(cardId))
      continue;
    if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;

    out[count].zone = NULL;
    out[count].gyIndex = (u8)(FUSION_EXTRA_SLOT_BASE + k);
    out[count].cardId = cardId;
    count++;
  }

  return count;
}

void AmazonessSecretArts_PayExtraDeckSource(const struct FusionMaterialSource *src)
{
  u16 *extra;
  u8 slot;
  u16 cardId;

  if (!AmazonessSecretArts_IsExtraDeckSource(src))
    return;

  slot = (u8)(src->gyIndex - FUSION_EXTRA_SLOT_BASE);
  extra = ActiveExtraDeck();
  cardId = extra[slot];
  if (cardId == CARD_NONE || cardId != src->cardId)
    return;

  extra[slot] = CARD_NONE;
  GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
  AmazonessSecretArts_ClearExtraMaterial();
}

u8 CanActivateAmazonessSecretArtsGy(u8 fixedDuelist, u8 gyIndex)
{
  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  if (EffectOpt_IsUsed(AMAZONESS_SECRET_ARTS))
    return FALSE;

  if (gyIndex >= GraveyardExpand_GetCount(fixedDuelist))
    return FALSE;

  if (GraveyardExpand_GetCardAt(fixedDuelist, gyIndex) != AMAZONESS_SECRET_ARTS)
    return FALSE;

  return ExtraDeckHasAmazonessMonster();
}

void ActivateAmazonessSecretArtsGy(u8 fixedDuelist, u8 gyIndex)
{
  if (!CanActivateAmazonessSecretArtsGy(fixedDuelist, gyIndex))
    return;

  Duel_ShowEffectText(AMAZONESS_SECRET_ARTS);
  if (IsDuelOver() == TRUE)
    return;

  EffectOpt_MarkUsed(AMAZONESS_SECRET_ARTS);
  Duel_BanishGraveyardAtFixed(fixedDuelist, gyIndex);
  ActivateExtraMaterialForTurn();

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void RunPlayerAmazonessSecretArtsFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  if (EffectOpt_IsUsed(AMAZONESS_SECRET_ARTS)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  sourceCount = FusionDuel_CollectHandAndFieldSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices),
                                                        RecipeIsAmazonessFusion);
  feasibleCount = FilterFeasibleByExtraDeck(feasibleIndices, feasibleCount);
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(AMAZONESS_SECRET_ARTS);
  if (IsDuelOver() == TRUE)
    return;

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe == NULL)
    return;

  FusionDuel_ExecutePolymerization(recipe, sources, sourceCount, AMAZONESS_SECRET_ARTS, FALSE);
  EffectOpt_MarkUsed(AMAZONESS_SECRET_ARTS);
}

static void AMAZONESS_SECRET_ARTS_ResolveBody(void)
{
  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    if (EffectOpt_IsUsed(AMAZONESS_SECRET_ARTS)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    sourceCount = FusionDuel_CollectHandAndFieldSources(sources, FUSION_MAX_SOURCES);
    if (sourceCount < 2) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, RecipeIsAmazonessFusion);
    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    FusionDuel_ExecutePolymerization(&gFusionRecipes[bestIdx], sources, sourceCount,
                                     AMAZONESS_SECRET_ARTS, TRUE);
    EffectOpt_MarkUsed(AMAZONESS_SECRET_ARTS);
    return;
  }

  RunPlayerAmazonessSecretArtsFlow();
}

APPEND_TEXT void EffectAMAZONESS_SECRET_ARTS(void)
{
  if (Duel_TryResolveSpellThroughTraps(AMAZONESS_SECRET_ARTS, AMAZONESS_SECRET_ARTS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
