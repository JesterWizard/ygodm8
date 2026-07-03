#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "fusion_duel.h"
#include "future_fusion.h"
#include "imperial_order.h"
#include "spell_effects.h"

#define FUTURE_FUSION_STANDBY_TURNS 2
#define FUTURE_FUSION_DECK_SOURCES 40
#define FUTURE_FUSION_LINKED_STAGE 2
#define FUTURE_FUSION_PICK_MENU_CAPACITY ((u8)ARRAY_COUNT(gDeckMenu.cards))

static u8 sSuppressFutureFusionLink APPEND_DATA = FALSE;

static const u8 sFutureFusionRecipeLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_FUSION_SUMMON,
};

static const u8 sFutureFusionMaterialLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FutureFusionMonsterRowForSpell(struct DuelCard *spellZone)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedZone(spellZone, &fixedRow, &col))
    return 0xFF;

  if (fixedRow == PLAYER_BACKROW)
    return PLAYER_MONSTER_ROW;

  if (fixedRow == OPPONENT_BACKROW)
    return OPPONENT_MONSTER_ROW;

  return 0xFF;
}

u8 IsActivatedFutureFusionZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == FUTURE_FUSION && zone->isFaceUp == TRUE
      && zone->isLocked == TRUE && zone->unk4 > 0;
}

static u8 IsPendingFutureFusionZone(const struct DuelCard *zone)
{
  return IsActivatedFutureFusionZone(zone) && zone->permStage < FUTURE_FUSION_LINKED_STAGE;
}

static u8 FutureFusionHasLinkedMonster(const struct DuelCard *zone)
{
  return IsActivatedFutureFusionZone(zone) && zone->permStage >= FUTURE_FUSION_LINKED_STAGE;
}

static struct DuelCard *FutureFusionGetLinkedMonster(struct DuelCard *spellZone)
{
  u8 monsterRow;
  u8 monsterCol;
  struct DuelCard *monster;

  if (!FutureFusionHasLinkedMonster(spellZone))
    return NULL;

  monsterRow = FutureFusionMonsterRowForSpell(spellZone);
  if (monsterRow == 0xFF)
    return NULL;

  monsterCol = spellZone->unk4 - 1;
  if (monsterCol >= MAX_ZONES_IN_ROW)
    return NULL;

  monster = gFixedZones[monsterRow][monsterCol];
  if (monster == NULL || monster->id == CARD_NONE)
    return NULL;

  if (GetTypeGroup(monster->id) != TYPE_GROUP_MONSTER)
    return NULL;

  return monster;
}

static u8 FutureFusionZoneTargetsMonster(struct DuelCard *spellZone, struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (!FutureFusionHasLinkedMonster(spellZone))
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return FALSE;

  return fixedRow == FutureFusionMonsterRowForSpell(spellZone)
      && fixedCol == spellZone->unk4 - 1;
}

static u8 SourceQualifies(const struct FusionRecipe *recipe,
                          const struct FusionMaterialSource *source, u16 need)
{
  if (recipe == NULL || source == NULL || source->cardId == CARD_NONE)
    return FALSE;

  /* ponytail: hand test copies of the fusion result are not valid materials. */
  if (source->cardId == recipe->result)
    return FALSE;

  return FusionRecipe_MaterialMatches(need, source->cardId);
}

static void PayDeckMaterials(const struct FusionMaterialSource *selected, u8 selectedCount)
{
  u8 i;

  for (i = 0; i < selectedCount; i++) {
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
  }

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
}

static u8 HasFeasibleDeckFusion(void)
{
  struct FusionMaterialSource sources[FUTURE_FUSION_DECK_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];

  sourceCount = FusionDuel_CollectDeckSources(sources, FUTURE_FUSION_DECK_SOURCES);
  if (sourceCount < 2)
    return FALSE;

  return FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                              ARRAY_COUNT(feasibleIndices), NULL) > 0;
}

u8 CanActivateFutureFusion(void)
{
  return HasFeasibleDeckFusion();
}

static void LoadRecipePickMenu(const u8 *recipeIndices, u8 count)
{
  u8 i;

  for (i = 0; i < FUTURE_FUSION_PICK_MENU_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < count; i++)
    gDeckMenu.cards[i] = gFusionRecipes[recipeIndices[i]].result;

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;
}

static const struct FusionRecipe *PlayerPickFusionRecipe(const u8 *recipeIndices, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;
  u8 chosenRecipeIdx = 0xFF;

  if (recipeIndices == NULL || count == 0)
    return NULL;

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&savedDeckMenu)[j] = ((u8 *)&gDeckMenu)[j];

  LoadRecipePickMenu(recipeIndices, count);

  if (!DeckMenuMainPickConfirmWithLabels(
          sFutureFusionRecipeLabels, ARRAY_COUNT(sFutureFusionRecipeLabels))) {
    for (j = 0; j < sizeof(gDeckMenu); j++)
      ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];
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

  if (chosenRecipeIdx == 0xFF)
    return NULL;

  return &gFusionRecipes[chosenRecipeIdx];
}

static s8 PlayerPickDeckMaterialSource(const struct FusionRecipe *recipe, u16 need,
                                       const struct FusionMaterialSource *sources,
                                       u8 sourceCount, const u8 *used)
{
  u8 sourceIndexMap[FUTURE_FUSION_DECK_SOURCES];
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 menuCount = 0;
  u8 i;
  u8 j;
  s8 chosen;

  for (i = 0; i < sourceCount; i++) {
    if (used[i])
      continue;
    if (!SourceQualifies(recipe, &sources[i], need))
      continue;

    sourceIndexMap[menuCount] = i;
    menuCount++;
  }

  if (menuCount == 0)
    return -1;

  if (menuCount == 1)
    return (s8)sourceIndexMap[0];

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&savedDeckMenu)[j] = ((u8 *)&gDeckMenu)[j];

  for (i = 0; i < FUTURE_FUSION_PICK_MENU_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < menuCount; i++)
    gDeckMenu.cards[i] = sources[sourceIndexMap[i]].cardId;

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;

  if (!DeckMenuMainPickConfirmWithLabels(
          sFutureFusionMaterialLabels, ARRAY_COUNT(sFutureFusionMaterialLabels))) {
    for (j = 0; j < sizeof(gDeckMenu); j++)
      ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];
    return -1;
  }

  chosen = (s8)sourceIndexMap[gDeckMenu.currentPos];

  for (j = 0; j < sizeof(gDeckMenu); j++)
    ((u8 *)&gDeckMenu)[j] = ((u8 *)&savedDeckMenu)[j];

  return chosen;
}

static u8 PlayerSelectDeckMaterials(const struct FusionRecipe *recipe,
                                    const struct FusionMaterialSource *sources,
                                    u8 sourceCount, struct FusionMaterialSource *selected)
{
  u8 used[FUSION_MAX_SOURCES];
  u8 matCount;
  u8 m;
  u8 i;

  if (recipe == NULL || sources == NULL || selected == NULL)
    return 0;

  matCount = FusionRecipe_MaterialCount(recipe);
  if (matCount < 2 || sourceCount < matCount)
    return 0;

  for (i = 0; i < FUSION_MAX_SOURCES; i++)
    used[i] = FALSE;

  for (m = 0; m < matCount; m++) {
    u16 need = FusionRecipe_MaterialAt(recipe, m);
    s8 sourceIndex = PlayerPickDeckMaterialSource(recipe, need, sources, sourceCount, used);

    if (sourceIndex < 0)
      return 0;

    used[sourceIndex] = TRUE;
    selected[m] = sources[sourceIndex];
  }

  return matCount;
}

static void ActivateFutureFusionWithMaterials(const struct FusionRecipe *recipe,
                                              const struct FusionMaterialSource *selected,
                                              u8 selectedCount)
{
  struct DuelCard *spellZone;
  u8 recipeIndex;

  if (recipe == NULL || selected == NULL
      || selectedCount != FusionRecipe_MaterialCount(recipe))
    return;

  recipeIndex = (u8)(recipe - gFusionRecipes);
  spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  if (spellZone == NULL || spellZone->id != FUTURE_FUSION)
    return;

  PayDeckMaterials(selected, selectedCount);
  Duel_ActivateContinuousZone(spellZone);
  ResetPermStage(spellZone);
  spellZone->unk4 = recipeIndex + 1;
}

static void RunPlayerFutureFusionFlow(void)
{
  struct FusionMaterialSource sources[FUTURE_FUSION_DECK_SOURCES];
  struct FusionMaterialSource selected[FUSION_MAX_MATERIALS];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  u8 selectedCount;
  const struct FusionRecipe *recipe;

  sourceCount = FusionDuel_CollectDeckSources(sources, FUTURE_FUSION_DECK_SOURCES);
  if (sourceCount < 2) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices), NULL);
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(FUTURE_FUSION);
  if (IsDuelOver() == TRUE)
    return;

  DeckMenu_BeginDuelTrunkView();

  recipe = PlayerPickFusionRecipe(feasibleIndices, feasibleCount);
  if (recipe == NULL) {
    DeckMenu_EndDuelTrunkView();
    return;
  }

  selectedCount = PlayerSelectDeckMaterials(recipe, sources, sourceCount, selected);
  DeckMenu_EndDuelTrunkView();
  if (selectedCount == 0)
    return;

  ActivateFutureFusionWithMaterials(recipe, selected, selectedCount);
}

static void LinkSummonedMonster(struct DuelCard *spellZone, struct DuelCard *monster)
{
  u8 fixedRow;
  u8 fixedCol;

  if (!Duel_FindFixedMonsterZone(monster, &fixedRow, &fixedCol)) {
    spellZone->unk4 = 0;
    return;
  }

  spellZone->permStage = FUTURE_FUSION_LINKED_STAGE;
  spellZone->unk4 = fixedCol + 1;
}

static void TrySummonPendingFutureFusion(struct DuelCard *spellZone)
{
  u8 recipeIndex;
  const struct FusionRecipe *recipe;
  s8 monsterCol;
  struct DuelCard *monster;

  if (!IsActivatedFutureFusionZone(spellZone)
      || spellZone->permStage != FUTURE_FUSION_STANDBY_TURNS)
    return;

  recipeIndex = spellZone->unk4 - 1;
  if (recipeIndex >= FusionRecipe_Count()) {
    spellZone->unk4 = 0;
    return;
  }

  recipe = &gFusionRecipes[recipeIndex];
  monsterCol = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (monsterCol < 0) {
    spellZone->unk4 = 0;
    return;
  }

  FusionDuel_SpecialSummonResult(recipe->result);

  monster = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][monsterCol];
  if (monster->id != recipe->result) {
    spellZone->unk4 = 0;
    return;
  }

  LinkSummonedMonster(spellZone, monster);
}

void TryApplyFutureFusionStandby(void)
{
  u8 i;
  struct DuelCard *spellZone;

  if (IsDuelOver() == TRUE || IsImperialOrderNegatingSpell(FUTURE_FUSION))
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    spellZone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];
    if (!IsPendingFutureFusionZone(spellZone))
      continue;

    IncrementPermStage(spellZone);
    if (spellZone->permStage < FUTURE_FUSION_STANDBY_TURNS)
      continue;

    TrySummonPendingFutureFusion(spellZone);
    if (IsDuelOver() == TRUE)
      return;
  }
}

static void DestroyLinkedMonsterForSpell(struct DuelCard *spellZone)
{
  struct DuelCard *monster;
  u8 fixedRow;
  u8 col;
  u8 graveyardDuelist;

  if (!FutureFusionHasLinkedMonster(spellZone))
    return;

  monster = FutureFusionGetLinkedMonster(spellZone);
  spellZone->unk4 = 0;
  spellZone->permStage = 0;

  if (monster == NULL || monster->id == CARD_NONE)
    return;

  if (!Duel_FindFixedMonsterZone(monster, &fixedRow, &col))
    return;

  graveyardDuelist = Duel_TurnDuelistMatchingWhoseTurn(Duel_FixedDuelistForMonsterRow(fixedRow));
  sSuppressFutureFusionLink = TRUE;
  Duel_DestroyZone(monster, graveyardDuelist, TRUE);
  sSuppressFutureFusionLink = FALSE;
}

void FutureFusion_OnZoneCleared(struct DuelCard *zone)
{
  if (sSuppressFutureFusionLink || zone == NULL || zone->id != FUTURE_FUSION)
    return;

  /* Pending: clearing the spell cancels the delayed summon (unk4/permStage die with zone). */
  if (FutureFusionHasLinkedMonster(zone))
    DestroyLinkedMonsterForSpell(zone);
}

void TryApplyFutureFusionOnMonsterLeave(struct DuelCard *zone)
{
  u8 row;
  u8 col;
  struct DuelCard *spellZone;
  u8 fixedRow;
  u8 spellCol;
  u8 graveyardDuelist;

  if (sSuppressFutureFusionLink || zone == NULL)
    return;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      spellZone = gFixedZones[row][col];
      if (!FutureFusionZoneTargetsMonster(spellZone, zone))
        continue;

      spellZone->unk4 = 0;
      spellZone->permStage = 0;
      if (!Duel_FindFixedZone(spellZone, &fixedRow, &spellCol))
        continue;

      graveyardDuelist = Duel_TurnDuelistMatchingWhoseTurn(
          (fixedRow == PLAYER_BACKROW) ? DUEL_PLAYER : DUEL_OPPONENT);
      sSuppressFutureFusionLink = TRUE;
      Duel_DestroyZone(spellZone, graveyardDuelist, TRUE);
      sSuppressFutureFusionLink = FALSE;
    }
  }
}

APPEND_TEXT void EffectFutureFusion(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (IsActivatedFutureFusionZone(spellZone)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (!CanActivateFutureFusion()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUTURE_FUSION_DECK_SOURCES];
    struct FusionMaterialSource selected[FUSION_MAX_MATERIALS];
    u8 sourceCount;
    u8 selectedCount;
    s8 bestIdx;

    sourceCount = FusionDuel_CollectDeckSources(sources, FUTURE_FUSION_DECK_SOURCES);
    bestIdx = FusionDuel_AiPickBestRecipeIndex(sources, sourceCount, NULL);
    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    selectedCount = FusionRecipe_SelectSources(&gFusionRecipes[bestIdx], sources, sourceCount,
                                               selected, FUSION_MAX_MATERIALS);
    if (selectedCount != FusionRecipe_MaterialCount(&gFusionRecipes[bestIdx])) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    Duel_ShowEffectText(FUTURE_FUSION);
    if (IsDuelOver() == TRUE)
      return;

    ActivateFutureFusionWithMaterials(&gFusionRecipes[bestIdx], selected, selectedCount);
    return;
  }

  RunPlayerFutureFusionFlow();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void FutureFusion_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = FUTURE_FUSION;
  zone.isFaceUp = TRUE;
  zone.isLocked = TRUE;
  zone.unk4 = 0;
  zone.permStage = 0;
  if (IsActivatedFutureFusionZone(&zone))
    __builtin_trap();

  zone.unk4 = 1;
  if (!IsPendingFutureFusionZone(&zone))
    __builtin_trap();

  zone.permStage = FUTURE_FUSION_LINKED_STAGE;
  if (!FutureFusionHasLinkedMonster(&zone))
    __builtin_trap();
}
#endif
