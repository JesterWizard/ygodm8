#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "elemental_hero_absolute_zero.h"
#include "fusion_duel.h"
#include "fusion_recipes.h"
#include "player_decks.h"
#include "spell_effects.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);
u8 ExtraDeck_TryRemoveCard(u16 cardId);

static const char sDarkMagicianName[] APPEND_RODATA = "Dark Magician";

static const u8 sEyeOfTimaeusPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_FUSION_SUMMON,
};

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsDarkMagicianMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == DARK_MAGICIAN || cardId == DARK_MAGICIAN_GIRL)
    return TRUE;

  return Duel_CardNameContains(cardId, sDarkMagicianName);
}

static u8 RecipeListsCardAsMaterial(const struct FusionRecipe *recipe, u16 cardId)
{
  u8 i;
  u8 matCount;

  if (recipe == NULL || cardId == CARD_NONE)
    return FALSE;

  matCount = FusionRecipe_MaterialCount(recipe);
  for (i = 0; i < matCount; i++) {
    u16 need = FusionRecipe_MaterialAt(recipe, i);

    /* Eye of Timaeus requires the targeted monster to be listed specifically. */
    if (FusionRecipe_MaterialIsConcrete(need) && need == cardId)
      return TRUE;
  }

  return FALSE;
}

static u8 ExtraDeckHasResult(u16 resultId)
{
  u16 *extra;
  u8 active;
  u8 k;

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

static u8 BuildFeasibleRecipesForMaterial(u16 materialId, u8 *outIndices, u8 maxOut)
{
  u8 count = 0;
  u8 i;
  u8 recipeCount = FusionRecipe_Count();

  for (i = 0; i < recipeCount && count < maxOut; i++) {
    const struct FusionRecipe *recipe = &gFusionRecipes[i];

    if (!RecipeListsCardAsMaterial(recipe, materialId))
      continue;

    if (gRuntimeConfig.enable_extra_deck && !ExtraDeckHasResult(recipe->result))
      continue;

    outIndices[count++] = i;
  }

  return count;
}

static u8 IsValidEyeOfTimaeusTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 feasible[32];

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  if (!IsDarkMagicianMonster(zone->id))
    return FALSE;

  return BuildFeasibleRecipesForMaterial(zone->id, feasible, ARRAY_COUNT(feasible)) > 0;
}

static u8 HasEyeOfTimaeusTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidEyeOfTimaeusTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateEyeOfTimaeus(void)
{
  if (EffectOpt_IsUsed(THE_EYE_OF_TIMAEUS))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  /* Need a free monster zone after using the material (material frees its zone). */
  return HasEyeOfTimaeusTarget();
}

static const struct FusionRecipe *PlayerPickEyeRecipe(const u8 *recipeIndices, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;
  u8 chosenIdx = 0xFF;

  if (recipeIndices == NULL || count == 0)
    return NULL;

  if (count == 1)
    return &gFusionRecipes[recipeIndices[0]];

  DECKMENU_SAVE();

  for (j = 0; j < EXTRA_DECK_SIZE; j++)
    gDeckMenu.cards[j] = CARD_NONE;
  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = gFusionRecipes[recipeIndices[j]].result;

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sEyeOfTimaeusPickLabels,
                                         ARRAY_COUNT(sEyeOfTimaeusPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return NULL;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  for (j = 0; j < count; j++) {
    if (gFusionRecipes[recipeIndices[j]].result == chosenId) {
      chosenIdx = recipeIndices[j];
      break;
    }
  }

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  if (chosenIdx == 0xFF)
    return NULL;

  return &gFusionRecipes[chosenIdx];
}

static const struct FusionRecipe *AiPickEyeRecipe(const u8 *recipeIndices, u8 count)
{
  u8 i;
  u16 bestAtk = 0;
  s8 best = -1;

  for (i = 0; i < count; i++) {
    u16 result = gFusionRecipes[recipeIndices[i]].result;

    SetCardInfo(result);
    if (best < 0 || gCardInfo.atk > bestAtk) {
      best = (s8)recipeIndices[i];
      bestAtk = gCardInfo.atk;
    }
  }

  if (best < 0)
    return NULL;

  return &gFusionRecipes[best];
}

static void ExecuteEyeOfTimaeus(struct DuelCard *materialZone, const struct FusionRecipe *recipe)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (materialZone == NULL || recipe == NULL)
    return;

  if (gRuntimeConfig.enable_extra_deck
      && (Duel_BlocksExtraDeckSpecialSummon(recipe->result)
          || !ExtraDeck_TryRemoveCard(recipe->result)))
    return;

  ElementalHeroAbsoluteZero_BeginSuppressLeave();
  ClearZoneAndSendMonToGraveyard(materialZone, ACTIVE_DUELIST);
  ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);
  FusionDuel_SpecialSummonResult(recipe->result, 1);
  ElementalHeroAbsoluteZero_EndSuppressLeave();
  UpdateDuelGfxExceptField();

  EffectOpt_MarkUsed(THE_EYE_OF_TIMAEUS);
}

static void ResolveEyeOfTimaeusTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *target;
  u8 feasible[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  if (!IsValidEyeOfTimaeusTarget(fixedRow, fixedCol))
    return;

  target = gFixedZones[fixedRow][fixedCol];
  feasibleCount = BuildFeasibleRecipesForMaterial(target->id, feasible, ARRAY_COUNT(feasible));
  if (feasibleCount == 0)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    recipe = PlayerPickEyeRecipe(feasible, feasibleCount);
  else
    recipe = AiPickEyeRecipe(feasible, feasibleCount);

  if (recipe == NULL)
    return;

  ExecuteEyeOfTimaeus(target, recipe);
}

static void CancelEyeOfTimaeusTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  UpdateDuelGfxExceptField();
}

static u8 AiPickEyeOfTimaeusTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidEyeOfTimaeusTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void THE_EYE_OF_TIMAEUS_ResolveBody(void)
{
  Duel_ShowEffectText(THE_EYE_OF_TIMAEUS);

  if (IsDuelOver() == TRUE || !CanActivateEyeOfTimaeus())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidEyeOfTimaeusTarget, ResolveEyeOfTimaeusTarget,
                     CancelEyeOfTimaeusTargeting, AiPickEyeOfTimaeusTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectTHE_EYE_OF_TIMAEUS(void)
{
  if (!CanActivateEyeOfTimaeus()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(THE_EYE_OF_TIMAEUS, THE_EYE_OF_TIMAEUS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void THE_EYE_OF_TIMAEUS_SelfCheck(void)
{
  if (!IsDarkMagicianMonster(DARK_MAGICIAN))
    while (1)
      ;
  if (!IsDarkMagicianMonster(DARK_MAGICIAN_GIRL))
    while (1)
      ;
  if (IsDarkMagicianMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!RecipeListsCardAsMaterial(FusionRecipe_FindByResult(AMULET_DRAGON), DARK_MAGICIAN))
    while (1)
      ;
}
#endif
