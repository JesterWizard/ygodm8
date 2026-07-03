#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel.h"
#include "duel_helpers.h"
#include "elemental_hero_electrum.h"
#include "elemental_hero_great_tornado.h"
#include "elemental_hero_gaia.h"
#include "elemental_hero_necroid_shaman.h"
#include "elemental_hero_absolute_zero.h"
#include "expanded_graveyard.h"
#include "fusion_duel.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyardDuelist);
void UpdateDuelGfxExceptField(void);

#define FUSION_PICK_MENU_CAPACITY ((u8)ARRAY_COUNT(gDeckMenu.cards))

static const u8 sFusionDuelPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_FUSION_SUMMON,
};

static void FusionDuel_LoadPickMenu(const u8 *recipeIndices, u8 count)
{
  u8 j;

  for (j = 0; j < FUSION_PICK_MENU_CAPACITY; j++)
    gDeckMenu.cards[j] = CARD_NONE;
  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = gFusionRecipes[recipeIndices[j]].result;

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

static u8 MaterialMatches(u16 need, u16 have, struct DuelCard *zone)
{
  u16 effective = Duel_GetEffectiveCardId(zone);

  if (zone == NULL)
    effective = have;

  return FusionRecipe_MaterialMatches(need, effective);
}

static void AddSource(struct FusionMaterialSource *out, u8 *count, u8 maxOut, struct DuelCard *zone,
                    u8 gyIndex, u16 cardId)
{
  if (*count >= maxOut || cardId == CARD_NONE)
    return;

  out[*count].zone = zone;
  out[*count].gyIndex = gyIndex;
  out[*count].cardId = cardId;
  (*count)++;
}

u8 FusionDuel_CollectHandAndFieldSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][i];
    if (zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      AddSource(out, &count, maxOut, zone, FUSION_GY_INDEX_NONE, zone->id);
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];
    if (zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      AddSource(out, &count, maxOut, zone, FUSION_GY_INDEX_NONE, zone->id);
  }

  return count;
}

u8 FusionDuel_CollectFieldAndGraveyardSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 gyCount;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];
    if (zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      AddSource(out, &count, maxOut, zone, FUSION_GY_INDEX_NONE, zone->id);
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER)
      AddSource(out, &count, maxOut, NULL, i, cardId);
  }

  return count;
}

u8 FusionDuel_CollectGraveyardElementalHeroSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 gyCount;
  u8 count = 0;
  u8 i;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;
    if (!Duel_IsElementalHeroCard(cardId))
      continue;
    AddSource(out, &count, maxOut, NULL, i, cardId);
  }

  return count;
}

static u8 SourceQualifiesAsFusionMaterial(const struct FusionRecipe *recipe,
                                        const struct FusionMaterialSource *source)
{
  if (recipe == NULL || source == NULL)
    return FALSE;

  /* ponytail: hand test copies of the fusion result are not valid materials. */
  if (source->cardId == recipe->result)
    return FALSE;

  return TRUE;
}

u8 FusionRecipe_IsFeasibleWithSources(const struct FusionRecipe *recipe,
                                      const struct FusionMaterialSource *sources,
                                      u8 sourceCount)
{
  u8 used[FUSION_MAX_SOURCES];
  u8 matCount;
  u8 m;
  u8 i;

  if (recipe == NULL || recipe->result == CARD_NONE)
    return FALSE;

  matCount = FusionRecipe_MaterialCount(recipe);
  if (matCount < 2 || sourceCount < matCount)
    return FALSE;

  for (i = 0; i < FUSION_MAX_SOURCES; i++)
    used[i] = FALSE;

  for (m = 0; m < matCount; m++) {
    u16 need = FusionRecipe_MaterialAt(recipe, m);
    u8 found = FALSE;

    for (i = 0; i < sourceCount; i++) {
      if (used[i])
        continue;
      if (!SourceQualifiesAsFusionMaterial(recipe, &sources[i]))
        continue;
      if (MaterialMatches(need, sources[i].cardId, sources[i].zone)) {
        used[i] = TRUE;
        found = TRUE;
        break;
      }
    }

    if (!found)
      return FALSE;
  }

  return TRUE;
}

u8 FusionRecipe_SelectSources(const struct FusionRecipe *recipe,
                              const struct FusionMaterialSource *sources, u8 sourceCount,
                              struct FusionMaterialSource *selected, u8 maxSelected)
{
  u8 used[FUSION_MAX_SOURCES];
  u8 matCount;
  u8 m;
  u8 i;
  u8 out = 0;

  if (recipe == NULL || selected == NULL)
    return 0;

  matCount = FusionRecipe_MaterialCount(recipe);
  if (maxSelected < matCount)
    return 0;

  for (i = 0; i < FUSION_MAX_SOURCES; i++)
    used[i] = FALSE;

  for (m = 0; m < matCount; m++) {
    u16 need = FusionRecipe_MaterialAt(recipe, m);
    u8 found = FALSE;

    for (i = 0; i < sourceCount; i++) {
      if (used[i])
        continue;
      if (!SourceQualifiesAsFusionMaterial(recipe, &sources[i]))
        continue;
      if (MaterialMatches(need, sources[i].cardId, sources[i].zone)) {
        used[i] = TRUE;
        selected[out++] = sources[i];
        found = TRUE;
        break;
      }
    }

    if (!found)
      return 0;
  }

  return out;
}

u8 FusionDuel_BuildFeasibleRecipeIndices(const struct FusionMaterialSource *sources,
                                         u8 sourceCount, u8 *outIndices, u8 maxOut,
                                         FusionRecipeFilterFn filter)
{
  u8 count = 0;
  u8 i;
  u8 recipeCount = FusionRecipe_Count();

  for (i = 0; i < recipeCount; i++) {
    const struct FusionRecipe *recipe = &gFusionRecipes[i];

    if (filter != NULL && !filter(recipe))
      continue;
    if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, sourceCount))
      continue;
    if (count >= maxOut)
      break;

    outIndices[count++] = i;
  }

  return count;
}

const struct FusionRecipe *FusionDuel_PlayerPickRecipe(const u8 *recipeIndices, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;
  u8 chosenRecipeIdx = 0xFF;

  if (recipeIndices == NULL || count == 0)
    return NULL;

  if (count == 1)
    return &gFusionRecipes[recipeIndices[0]];

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&savedDeckMenu)[j] = ((u8 *)&gDeckMenu)[j];

  FusionDuel_LoadPickMenu(recipeIndices, count);

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sFusionDuelPickLabels, ARRAY_COUNT(sFusionDuelPickLabels))) {
    for (j = 0; j < sizeof(gDeckMenu); j++)
      ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];

    DeckMenu_EndDuelTrunkView();
    return NULL;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  for (j = 0; j < count; j++) {
    if (gFusionRecipes[recipeIndices[j]].result == chosenId) {
      chosenRecipeIdx = recipeIndices[j];
      break;
    }
  }

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];

  DeckMenu_EndDuelTrunkView();

  if (chosenRecipeIdx == 0xFF)
    return NULL;

  return &gFusionRecipes[chosenRecipeIdx];
}

const struct FusionRecipe *FusionDuel_PlayerConfirmFusionPick(const u8 *recipeIndices, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;
  u8 chosenRecipeIdx = 0xFF;

  if (recipeIndices == NULL || count == 0)
    return NULL;

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&savedDeckMenu)[j] = ((u8 *)&gDeckMenu)[j];

  FusionDuel_LoadPickMenu(recipeIndices, count);

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sFusionDuelPickLabels, ARRAY_COUNT(sFusionDuelPickLabels))) {
    for (j = 0; j < sizeof(gDeckMenu); j++)
      ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];

    DeckMenu_EndDuelTrunkView();
    return NULL;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  for (j = 0; j < count; j++) {
    if (gFusionRecipes[recipeIndices[j]].result == chosenId) {
      chosenRecipeIdx = recipeIndices[j];
      break;
    }
  }

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];

  DeckMenu_EndDuelTrunkView();

  if (chosenRecipeIdx == 0xFF)
    return NULL;

  return &gFusionRecipes[chosenRecipeIdx];
}

static void PayPolymerizationMaterials(const struct FusionMaterialSource *selected, u8 selectedCount)
{
  u8 i;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone != NULL)
      ClearZoneAndSendMonToGraveyard(selected[i].zone, ACTIVE_DUELIST);
  }
}

static void PayMiracleFusionMaterials(const struct FusionMaterialSource *selected, u8 selectedCount)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 gyIndices[FUSION_MAX_MATERIALS];
  u8 gyCount = 0;
  u8 i;
  u8 g;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].gyIndex != FUSION_GY_INDEX_NONE)
      gyIndices[gyCount++] = selected[i].gyIndex;
  }

  while (gyCount > 0) {
    u8 best = 0;
    for (g = 1; g < gyCount; g++) {
      if (gyIndices[g] > gyIndices[best])
        best = g;
    }
    GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndices[best]);
    gyIndices[best] = gyIndices[gyCount - 1];
    gyCount--;
  }
}

static void SummonFusionResult(u16 resultId)
{
  struct DuelSummonOpts opts;
  u8 i;

  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, resultId, opts);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];
    if (zone->id == resultId && zone->isFaceUp) {
      /* Great Tornado's halving is continuous while face-up on the field. */
      if (resultId != ELEMENTAL_HERO_GREAT_TORNADO
          && resultId != ELEMENTAL_HERO_ABSOLUTE_ZERO
          && resultId != ELEMENTAL_HERO_GAIA
          && resultId != ELEMENTAL_HERO_NECROID_SHAMAN)
        FlipCardFaceDown(zone);
      break;
    }
  }

  UpdateDuelGfxExceptField();

  if (resultId == ELEMENTAL_HERO_ELECTRUM)
    ElementalHeroElectrum_OnFusionSummoned();

  if (resultId == ELEMENTAL_HERO_GREAT_TORNADO)
    ElementalHeroGreatTornado_OnFusionSummoned();

  if (resultId == ELEMENTAL_HERO_GAIA)
    ElementalHeroGaia_OnFusionSummoned();

  if (resultId == ELEMENTAL_HERO_NECROID_SHAMAN)
    ElementalHeroNecroidShaman_OnFusionSummoned();
}

static enum DuelActionResult ExecuteFusionRecipe(const struct FusionRecipe *recipe,
                                                 const struct FusionMaterialSource *sources,
                                                 u8 sourceCount, u16 spellCardId,
                                                 void (*payMaterials)(const struct FusionMaterialSource *,
                                                                      u8),
                                                 u8 showEffectText)
{
  struct FusionMaterialSource selected[FUSION_MAX_MATERIALS];
  u8 selectedCount;
  s8 emptyZone;

  if (recipe == NULL || payMaterials == NULL)
    return DUEL_ACTION_INVALID;

  selectedCount = FusionRecipe_SelectSources(recipe, sources, sourceCount, selected,
                                             FUSION_MAX_MATERIALS);
  if (selectedCount != FusionRecipe_MaterialCount(recipe))
    return DUEL_ACTION_NO_TARGET;

  emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (emptyZone < 0)
    return DUEL_ACTION_NO_ZONE;

  if (showEffectText) {
    Duel_ShowEffectText(spellCardId);
    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  ElementalHeroAbsoluteZero_BeginSuppressLeave();
  payMaterials(selected, selectedCount);
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);
  SummonFusionResult(recipe->result);
  ElementalHeroAbsoluteZero_EndSuppressLeave();
  return DUEL_ACTION_OK;
}

void FusionDuel_ExecutePolymerization(const struct FusionRecipe *recipe,
                                    const struct FusionMaterialSource *sources,
                                    u8 sourceCount, u16 spellCardId, u8 showEffectText)
{
  ExecuteFusionRecipe(recipe, sources, sourceCount, spellCardId, PayPolymerizationMaterials,
                      showEffectText);
}

void FusionDuel_ExecuteMiracleFusion(const struct FusionRecipe *recipe,
                                     const struct FusionMaterialSource *sources,
                                     u8 sourceCount, u16 spellCardId, u8 showEffectText)
{
  ExecuteFusionRecipe(recipe, sources, sourceCount, spellCardId, PayMiracleFusionMaterials,
                      showEffectText);
}

s8 FusionDuel_AiPickBestRecipeIndex(const struct FusionMaterialSource *sources,
                                    u8 sourceCount, FusionRecipeFilterFn filter)
{
  u8 i;
  u16 bestAtk = 0;
  s8 bestIdx = -1;
  u8 recipeCount = FusionRecipe_Count();

  for (i = 0; i < recipeCount; i++) {
    const struct FusionRecipe *recipe = &gFusionRecipes[i];

    if (filter != NULL && !filter(recipe))
      continue;
    if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, sourceCount))
      continue;

    SetCardInfo(recipe->result);
    if (bestIdx < 0 || gCardInfo.atk > bestAtk) {
      bestIdx = (s8)i;
      bestAtk = gCardInfo.atk;
    }
  }

  return bestIdx;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void FusionDuel_SelfCheck(void)
{
  const struct FusionRecipe *recipe = FusionRecipe_FindByResult(ELEMENTAL_HERO_ABSOLUTE_ZERO);
  struct FusionMaterialSource sources[4];
  struct FusionMaterialSource selected[2];
  u8 selectedCount;

  if (recipe == NULL)
    while (1)
      ;

  sources[0].zone = NULL;
  sources[0].gyIndex = FUSION_GY_INDEX_NONE;
  sources[0].cardId = ELEMENTAL_HERO_ABSOLUTE_ZERO;
  sources[1].zone = NULL;
  sources[1].gyIndex = FUSION_GY_INDEX_NONE;
  sources[1].cardId = ELEMENTAL_HERO_OCEAN;

  if (FusionRecipe_IsFeasibleWithSources(recipe, sources, 2))
    while (1)
      ;

  sources[0].cardId = ELEMENTAL_HERO_AVIAN;
  if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, 2))
    while (1)
      ;

  selectedCount = FusionRecipe_SelectSources(recipe, sources, 2, selected, 2);
  if (selectedCount != 2)
    while (1)
      ;

  if (selected[0].cardId == ELEMENTAL_HERO_ABSOLUTE_ZERO
      || selected[1].cardId == ELEMENTAL_HERO_ABSOLUTE_ZERO)
    while (1)
      ;
}
#endif
