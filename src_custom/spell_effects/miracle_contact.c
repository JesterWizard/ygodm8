#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "elemental_hero_absolute_zero.h"
#include "expanded_graveyard.h"
#include "fusion_duel.h"
#include "spell_effects.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

/* Classic Contact Fusion Neos recipes (list Elemental HERO Neos as material).
 * ponytail: not in gFusionRecipes — local table only. Ceiling: misses newer Neos
 * Fusions / Brave Neos Neo-Spacian wildcard; upgrade: add to fusion_recipes.c. */
static const struct FusionRecipe sMiracleContactRecipes[] APPEND_RODATA = {
  { ELEMENTAL_HERO_AIR_NEOS, ELEMENTAL_HERO_NEOS, NEO_SPACIAN_AIR_HUMMINGBIRD, 0, 0 },
  { ELEMENTAL_HERO_AQUA_NEOS, ELEMENTAL_HERO_NEOS, NEO_SPACIAN_AQUA_DOLPHIN, 0, 0 },
  { ELEMENTAL_HERO_DARK_NEOS, ELEMENTAL_HERO_NEOS, NEO_SPACIAN_DARK_PANTHER, 0, 0 },
  { ELEMENTAL_HERO_FLARE_NEOS, ELEMENTAL_HERO_NEOS, NEO_SPACIAN_FLARE_SCARAB, 0, 0 },
  { ELEMENTAL_HERO_GLOW_NEOS, ELEMENTAL_HERO_NEOS, NEO_SPACIAN_GLOW_MOSS, 0, 0 },
  { ELEMENTAL_HERO_GRAND_NEOS, ELEMENTAL_HERO_NEOS, NEO_SPACIAN_GRAND_MOLE, 0, 0 },
  { ELEMENTAL_HERO_MARINE_NEOS, ELEMENTAL_HERO_NEOS, NEO_SPACIAN_MARINE_DOLPHIN, 0, 0 },
  { ELEMENTAL_HERO_STORM_NEOS, ELEMENTAL_HERO_NEOS, NEO_SPACIAN_AIR_HUMMINGBIRD,
    NEO_SPACIAN_AQUA_DOLPHIN, 0 },
  { ELEMENTAL_HERO_MAGMA_NEOS, ELEMENTAL_HERO_NEOS, NEO_SPACIAN_FLARE_SCARAB,
    NEO_SPACIAN_GRAND_MOLE, 0 },
  { ELEMENTAL_HERO_CHAOS_NEOS, ELEMENTAL_HERO_NEOS, NEO_SPACIAN_DARK_PANTHER,
    NEO_SPACIAN_GLOW_MOSS, 0 },
};

static const u8 sMiracleContactPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 MiracleContactRecipeCount(void)
{
  return ARRAY_COUNT(sMiracleContactRecipes);
}

static u8 RecipeListsElementalHeroNeos(const struct FusionRecipe *recipe)
{
  u8 i;
  u8 matCount;

  if (recipe == NULL)
    return FALSE;

  if (!Duel_IsElementalHeroCard(recipe->result))
    return FALSE;

  matCount = FusionRecipe_MaterialCount(recipe);
  for (i = 0; i < matCount; i++) {
    if (FusionRecipe_MaterialAt(recipe, i) == ELEMENTAL_HERO_NEOS)
      return TRUE;
  }

  return FALSE;
}

static u8 BuildFeasibleMiracleContactIndices(const struct FusionMaterialSource *sources,
                                             u8 sourceCount, u8 *outIndices, u8 maxOut)
{
  u8 count = 0;
  u8 i;
  u8 recipeCount = MiracleContactRecipeCount();

  for (i = 0; i < recipeCount; i++) {
    const struct FusionRecipe *recipe = &sMiracleContactRecipes[i];

    if (!RecipeListsElementalHeroNeos(recipe))
      continue;
    if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, sourceCount))
      continue;
    if (count >= maxOut)
      break;

    outIndices[count++] = i;
  }

  return count;
}

static void ReturnCardToDeck(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static void PayMiracleContactMaterials(const struct FusionMaterialSource *selected,
                                       u8 selectedCount)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 gyIndices[FUSION_MAX_MATERIALS];
  u8 gyCount = 0;
  u8 i;
  u8 g;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone != NULL) {
      u16 cardId = selected[i].zone->id;

      ClearZone(selected[i].zone);
      ReturnCardToDeck(ACTIVE_DUELIST, cardId);
    } else if (selected[i].gyIndex != FUSION_GY_INDEX_NONE) {
      gyIndices[gyCount++] = selected[i].gyIndex;
    }
  }

  while (gyCount > 0) {
    u8 best = 0;

    for (g = 1; g < gyCount; g++) {
      if (gyIndices[g] > gyIndices[best])
        best = g;
    }

    {
      u16 cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndices[best]);

      ReturnCardToDeck(ACTIVE_DUELIST, cardId);
    }

    gyIndices[best] = gyIndices[gyCount - 1];
    gyCount--;
  }

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
}

static const struct FusionRecipe *PlayerPickMiracleContactRecipe(const u8 *recipeIndices,
                                                                 u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;
  u8 chosenLocalIdx = 0xFF;

  if (recipeIndices == NULL || count == 0)
    return NULL;

  if (count == 1)
    return &sMiracleContactRecipes[recipeIndices[0]];

  DECKMENU_SAVE();

  for (j = 0; j < EXPANDED_GRAVEYARD_CAPACITY; j++)
    gDeckMenu.cards[j] = CARD_NONE;

  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = sMiracleContactRecipes[recipeIndices[j]].result;

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sMiracleContactPickLabels, ARRAY_COUNT(sMiracleContactPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return NULL;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  for (j = 0; j < count; j++) {
    if (sMiracleContactRecipes[recipeIndices[j]].result == chosenId) {
      chosenLocalIdx = recipeIndices[j];
      break;
    }
  }

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  if (chosenLocalIdx == 0xFF)
    return NULL;

  return &sMiracleContactRecipes[chosenLocalIdx];
}

static s8 AiPickBestMiracleContactIndex(const struct FusionMaterialSource *sources,
                                        u8 sourceCount)
{
  u8 i;
  u16 bestAtk = 0;
  s8 bestIdx = -1;
  u8 recipeCount = MiracleContactRecipeCount();

  for (i = 0; i < recipeCount; i++) {
    const struct FusionRecipe *recipe = &sMiracleContactRecipes[i];
    u16 candidateAtk;

    if (!RecipeListsElementalHeroNeos(recipe))
      continue;
    if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, sourceCount))
      continue;

    SetCardInfo(recipe->result);
    candidateAtk = gCardInfo.atk;

    if (bestIdx < 0 || candidateAtk > bestAtk) {
      bestIdx = (s8)i;
      bestAtk = candidateAtk;
    }
  }

  return bestIdx;
}

static void ExecuteMiracleContact(const struct FusionRecipe *recipe,
                                  const struct FusionMaterialSource *sources, u8 sourceCount,
                                  u8 showEffectText)
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
    Duel_ShowEffectText(MIRACLE_CONTACT);
    if (IsDuelOver() == TRUE)
      return;
  }

  ElementalHeroAbsoluteZero_BeginSuppressLeave();
  PayMiracleContactMaterials(selected, selectedCount);
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);
  FusionDuel_SpecialSummonResult(recipe->result, selectedCount);
  ElementalHeroAbsoluteZero_EndSuppressLeave();
  UpdateDuelGfxExceptField();
}

static void RunPlayerMiracleContactFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  sourceCount = FusionDuel_CollectHandFieldAndGraveyardSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = BuildFeasibleMiracleContactIndices(sources, sourceCount, feasibleIndices,
                                                     ARRAY_COUNT(feasibleIndices));
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(MIRACLE_CONTACT);
  if (IsDuelOver() == TRUE)
    return;

  recipe = PlayerPickMiracleContactRecipe(feasibleIndices, feasibleCount);
  if (recipe == NULL)
    return;

  ExecuteMiracleContact(recipe, sources, sourceCount, FALSE);
}

static void MIRACLE_CONTACT_ResolveBody(void)
{
  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    sourceCount = FusionDuel_CollectHandFieldAndGraveyardSources(sources, FUSION_MAX_SOURCES);
    if (sourceCount < 2) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    bestIdx = AiPickBestMiracleContactIndex(sources, sourceCount);
    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ExecuteMiracleContact(&sMiracleContactRecipes[bestIdx], sources, sourceCount, TRUE);
    return;
  }

  RunPlayerMiracleContactFlow();
}

APPEND_TEXT void EffectMIRACLE_CONTACT(void)
{
  if (Duel_TryResolveSpellThroughTraps(MIRACLE_CONTACT, MIRACLE_CONTACT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MIRACLE_CONTACT_SelfCheck(void)
{
  if (!RecipeListsElementalHeroNeos(&sMiracleContactRecipes[0]))
    while (1)
      ;
  if (FusionRecipe_MaterialAt(&sMiracleContactRecipes[0], 0) != ELEMENTAL_HERO_NEOS)
    while (1)
      ;
}
#endif
