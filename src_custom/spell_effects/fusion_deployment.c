#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "fusion_deployment.h"
#include "fusion_recipes.h"
#include "player_decks.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */
static u8 sFusionDeploymentFusionOnlyLock APPEND_DATA = {0};

u8 FusionDeployment_IsLocked(void)
{
  return sFusionDeploymentFusionOnlyLock;
}

void FusionDeployment_MarkLocked(void)
{
  sFusionDeploymentFusionOnlyLock = TRUE;
}

void FusionDeployment_ClearOnTurnBoundary(void)
{
  sFusionDeploymentFusionOnlyLock = FALSE;
}

static const u8 sFusionDeploymentPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u16 *ActiveExtraDeck(void)
{
  u8 active = gActiveDeckIndex;

  if (active >= PLAYER_DECK_INDEX_MIN && active <= PLAYER_DECK_INDEX_MAX) {
    switch (active) {
    case 1:
      return gPlayerDeck1ExtraDeck;
    case 2:
      return gPlayerDeck2ExtraDeck;
    case 3:
      return gPlayerDeck3ExtraDeck;
    default:
      return gPlayerDeck1ExtraDeck;
    }
  }

  return gPlayerDeck1ExtraDeck;
}

static u8 IsFusionMonsterCard(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == FUSION_CARD;
}

static u8 HandHasCardId(u16 cardId)
{
  return RowHasCardMatch(gTurnHands[ACTIVE_DUELIST], cardId);
}

static u8 MaterialAvailableInHandOrDeck(u16 materialId)
{
  if (!FusionRecipe_MaterialIsConcrete(materialId))
    return FALSE;

  if (Duel_CardCannotBeSpecialSummoned(materialId))
    return FALSE;

  if (HandHasCardId(materialId))
    return TRUE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, materialId) >= 0;
}

static u8 FusionHasAvailableListedMaterial(u16 fusionId)
{
  const struct FusionRecipe *recipe;
  u8 i;
  u8 materialCount;

  recipe = FusionRecipe_FindByResult(fusionId);
  if (recipe == NULL)
    return FALSE;

  materialCount = FusionRecipe_MaterialCount(recipe);
  for (i = 0; i < materialCount; i++) {
    if (MaterialAvailableInHandOrDeck(FusionRecipe_MaterialAt(recipe, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 LoadRevealFusionMenu(u16 *fusionIdOut)
{
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  if (gRuntimeConfig.enable_extra_deck) {
    u16 *extra = ActiveExtraDeck();

    for (i = 0; i < EXTRA_DECK_SIZE; i++) {
      u16 cardId = extra[i];

      if (!IsFusionMonsterCard(cardId))
        continue;
      if (!FusionHasAvailableListedMaterial(cardId))
        continue;

      fusionIdOut[menuCount] = cardId;
      gDeckMenu.cards[menuCount] = cardId;
      menuCount++;
    }
  } else {
    /* ponytail: Extra Deck disabled — browse gFusionRecipes results instead.
     * Ceiling: not a real ED reveal; upgrade: require enable_extra_deck. */
    u8 recipeCount = FusionRecipe_Count();

    for (i = 0; i < recipeCount && menuCount < EXPANDED_GRAVEYARD_CAPACITY; i++) {
      u16 result = gFusionRecipes[i].result;

      if (!IsFusionMonsterCard(result))
        continue;
      if (!FusionHasAvailableListedMaterial(result))
        continue;

      /* Dedupe identical results. */
      {
        u8 j;
        u8 seen = FALSE;

        for (j = 0; j < menuCount; j++) {
          if (fusionIdOut[j] == result) {
            seen = TRUE;
            break;
          }
        }
        if (seen)
          continue;
      }

      fusionIdOut[menuCount] = result;
      gDeckMenu.cards[menuCount] = result;
      menuCount++;
    }
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static u16 PickRevealFusion(void)
{
  u16 fusionIds[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u16 chosen;

  DECKMENU_SAVE();

  menuCount = LoadRevealFusionMenu(fusionIds);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return CARD_NONE;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    chosen = fusionIds[0];
    DECKMENU_RESTORE();
    return chosen;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sFusionDeploymentPickLabels, ARRAY_COUNT(sFusionDeploymentPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  chosen = fusionIds[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return chosen;
}

static u8 LoadMaterialMenu(u16 fusionId, u16 *materialOut)
{
  const struct FusionRecipe *recipe;
  u8 materialCount;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  recipe = FusionRecipe_FindByResult(fusionId);
  if (recipe == NULL)
    return 0;

  materialCount = FusionRecipe_MaterialCount(recipe);
  for (i = 0; i < materialCount; i++) {
    u16 materialId = FusionRecipe_MaterialAt(recipe, i);
    u8 j;
    u8 seen = FALSE;

    if (!MaterialAvailableInHandOrDeck(materialId))
      continue;

    for (j = 0; j < menuCount; j++) {
      if (materialOut[j] == materialId) {
        seen = TRUE;
        break;
      }
    }
    if (seen)
      continue;

    materialOut[menuCount] = materialId;
    gDeckMenu.cards[menuCount] = materialId;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static u16 PickListedMaterial(u16 fusionId)
{
  u16 materials[FUSION_MAX_MATERIALS];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u16 chosen;

  DECKMENU_SAVE();

  menuCount = LoadMaterialMenu(fusionId, materials);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return CARD_NONE;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    chosen = materials[0];
    DECKMENU_RESTORE();
    return chosen;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sFusionDeploymentPickLabels, ARRAY_COUNT(sFusionDeploymentPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  chosen = materials[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return chosen;
}

static s8 PickHandZoneWithId(u16 cardId)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == cardId)
      return (s8)i;
  }

  return -1;
}

static enum DuelActionResult SpecialSummonMaterialFromHandOrDeck(u16 materialId)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 handZone;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (HandHasCardId(materialId)) {
    if (WhoseTurn() == DUEL_PLAYER)
      return Duel_SpecialSummonFromHand(ACTIVE_DUELIST, materialId, NULL, opts);

    handZone = PickHandZoneWithId(materialId);
    if (handZone < 0)
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts);
  }

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, materialId) >= 0)
    return Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, materialId, opts);

  return DUEL_ACTION_NO_TARGET;
}

static u8 CanActivateFusionDeployment(void)
{
  u16 fusionIds[EXPANDED_GRAVEYARD_CAPACITY];
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 menuCount;

  if (EffectOpt_IsUsed(FUSION_DEPLOYMENT))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  DECKMENU_SAVE();
  menuCount = LoadRevealFusionMenu(fusionIds);
  DECKMENU_RESTORE();

  return menuCount > 0;
}

static void FUSION_DEPLOYMENT_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u16 fusionId;
  u16 materialId;
  enum DuelActionResult summonResult;

  Duel_ShowEffectText(FUSION_DEPLOYMENT);

  if (IsDuelOver() == TRUE || !CanActivateFusionDeployment())
    return;

  fusionId = PickRevealFusion();
  if (fusionId == CARD_NONE)
    return;

  materialId = PickListedMaterial(fusionId);
  if (materialId == CARD_NONE)
    return;

  if (spellZone != NULL && spellZone->id == FUSION_DEPLOYMENT)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  EffectOpt_MarkUsed(FUSION_DEPLOYMENT);

  summonResult = SpecialSummonMaterialFromHandOrDeck(materialId);
  if (summonResult != DUEL_ACTION_OK)
    return;

  FusionDeployment_MarkLocked();

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectFUSION_DEPLOYMENT(void)
{
  if (!CanActivateFusionDeployment()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(FUSION_DEPLOYMENT, FUSION_DEPLOYMENT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void FUSION_DEPLOYMENT_SelfCheck(void)
{
  if (!FusionRecipe_MaterialIsConcrete(ELEMENTAL_HERO_AVIAN))
    while (1)
      ;
  if (FusionRecipe_MaterialIsConcrete(FUSION_RECIPE_WILDCARD))
    while (1)
      ;
}
#endif
