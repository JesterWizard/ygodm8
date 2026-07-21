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
#include "elemental_hero_absolute_zero.h"
#include "expanded_graveyard.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"
#include "the_gaze_of_timaeus.h"

void ClearZone(struct DuelCard *zone);
void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);
u8 ExtraDeck_TryRemoveCard(u16 cardId);

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */

static u8 sGazeStampRow APPEND_DATA = {0xFF};
static u8 sGazeStampCol APPEND_DATA = {0xFF};
static u16 sGazeStampId APPEND_DATA = {CARD_NONE};
static u8 sGazeStampTurnsLeft APPEND_DATA = {0};

static const u8 sGazePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* Eye of Timaeus-style Fusion results that mention DM/DMG (local + gFusionRecipes). */
static const struct {
  u16 result;
  u16 mentioned;
} sGazeMentionFusions[] APPEND_RODATA = {
  { AMULET_DRAGON, DARK_MAGICIAN },
  { DARK_MAGICIAN_THE_DRAGON_KNIGHT, DARK_MAGICIAN },
  { DARK_PALADIN, DARK_MAGICIAN },
  { DARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT, DARK_MAGICIAN_GIRL },
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDarkMagicianOrGirl(u16 cardId)
{
  return cardId == DARK_MAGICIAN || cardId == DARK_MAGICIAN_GIRL;
}

static u8 RecipeListsConcreteMaterial(const struct FusionRecipe *recipe, u16 materialId)
{
  u8 i;
  u8 matCount;

  if (recipe == NULL || materialId == CARD_NONE)
    return FALSE;

  matCount = FusionRecipe_MaterialCount(recipe);
  for (i = 0; i < matCount; i++) {
    u16 need = FusionRecipe_MaterialAt(recipe, i);

    if (FusionRecipe_MaterialIsConcrete(need) && need == materialId)
      return TRUE;
  }

  return FALSE;
}

static u8 FusionMentionsMaterial(u16 resultId, u16 materialId)
{
  const struct FusionRecipe *recipe;
  u8 i;

  if (resultId == CARD_NONE || materialId == CARD_NONE)
    return FALSE;

  for (i = 0; i < ARRAY_COUNT(sGazeMentionFusions); i++) {
    if (sGazeMentionFusions[i].result == resultId
        && sGazeMentionFusions[i].mentioned == materialId)
      return TRUE;
  }

  recipe = FusionRecipe_FindByResult(resultId);
  return RecipeListsConcreteMaterial(recipe, materialId);
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

static u8 BuildMentionFusionTargets(u16 materialId, u16 *outIds, u8 maxOut)
{
  u8 count = 0;
  u8 i;
  u8 j;
  u8 recipeCount;

  if (outIds == NULL || maxOut == 0 || materialId == CARD_NONE)
    return 0;

  for (i = 0; i < ARRAY_COUNT(sGazeMentionFusions) && count < maxOut; i++) {
    u16 result = sGazeMentionFusions[i].result;
    u8 dup = FALSE;

    if (sGazeMentionFusions[i].mentioned != materialId)
      continue;
    if (gRuntimeConfig.enable_extra_deck && !ExtraDeckHasResult(result))
      continue;

    for (j = 0; j < count; j++) {
      if (outIds[j] == result) {
        dup = TRUE;
        break;
      }
    }
    if (dup)
      continue;

    outIds[count++] = result;
  }

  recipeCount = FusionRecipe_Count();
  for (i = 0; i < recipeCount && count < maxOut; i++) {
    const struct FusionRecipe *recipe = &gFusionRecipes[i];
    u16 result = recipe->result;
    u8 dup = FALSE;

    if (!RecipeListsConcreteMaterial(recipe, materialId))
      continue;
    if (gRuntimeConfig.enable_extra_deck && !ExtraDeckHasResult(result))
      continue;

    for (j = 0; j < count; j++) {
      if (outIds[j] == result) {
        dup = TRUE;
        break;
      }
    }
    if (dup)
      continue;

    outIds[count++] = result;
  }

  return count;
}

static u8 CollectDmDmgSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 gyCount;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone == NULL || zone->id == CARD_NONE || !IsDarkMagicianOrGirl(zone->id))
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

    if (!IsDarkMagicianOrGirl(cardId))
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

static u8 HasUsableGazeTarget(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u16 fusions[EXTRA_DECK_SIZE];
  u8 i;

  if (EffectOpt_IsUsed(THE_GAZE_OF_TIMAEUS))
    return FALSE;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;
  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  sourceCount = CollectDmDmgSources(sources, FUSION_MAX_SOURCES);
  for (i = 0; i < sourceCount; i++) {
    if (BuildMentionFusionTargets(sources[i].cardId, fusions, EXTRA_DECK_SIZE) > 0)
      return TRUE;
  }

  return FALSE;
}

static u8 PlayerPickSourceIndex(const struct FusionMaterialSource *sources, u8 sourceCount)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;
  u8 chosenIdx = 0xFF;

  if (sources == NULL || sourceCount == 0)
    return 0xFF;
  if (sourceCount == 1)
    return 0;

  DECKMENU_SAVE();

  for (j = 0; j < EXPANDED_GRAVEYARD_CAPACITY; j++)
    gDeckMenu.cards[j] = CARD_NONE;
  for (j = 0; j < sourceCount; j++)
    gDeckMenu.cards[j] = sources[j].cardId;

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = sourceCount;

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sGazePickLabels, ARRAY_COUNT(sGazePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  for (j = 0; j < sourceCount; j++) {
    if (sources[j].cardId == chosenId) {
      chosenIdx = j;
      break;
    }
  }

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenIdx;
}

static u16 PlayerPickFusionResult(const u16 *targetIds, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;

  if (targetIds == NULL || count == 0)
    return CARD_NONE;
  if (count == 1)
    return targetIds[0];

  DECKMENU_SAVE();

  for (j = 0; j < EXTRA_DECK_SIZE; j++)
    gDeckMenu.cards[j] = CARD_NONE;
  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = targetIds[j];

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sGazePickLabels, ARRAY_COUNT(sGazePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenId;
}

static u16 AiPickFusionResult(const u16 *targetIds, u8 count)
{
  u8 i;
  u16 bestId = CARD_NONE;
  u16 bestAtk = 0;

  for (i = 0; i < count; i++) {
    SetCardInfo(targetIds[i]);
    if (bestId == CARD_NONE || gCardInfo.atk > bestAtk) {
      bestId = targetIds[i];
      bestAtk = gCardInfo.atk;
    }
  }

  return bestId;
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

static void ShuffleSourceIntoDeck(const struct FusionMaterialSource *source)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;

  if (source == NULL)
    return;

  if (source->zone != NULL) {
    cardId = source->zone->id;
    ClearZone(source->zone);
    ReturnCardToDeck(ACTIVE_DUELIST, cardId);
  } else if (source->gyIndex != FUSION_GY_INDEX_NONE) {
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, source->gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    GraveyardExpand_RefreshDisplay();
    ReturnCardToDeck(ACTIVE_DUELIST, cardId);
  }

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
}

static void ExecuteGazeFusion(const struct FusionMaterialSource *source, u16 resultId)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (source == NULL || resultId == CARD_NONE || !FusionMentionsMaterial(resultId, source->cardId))
    return;

  if (gRuntimeConfig.enable_extra_deck
      && (Duel_BlocksExtraDeckSpecialSummon(resultId) || !ExtraDeck_TryRemoveCard(resultId)))
    return;

  ElementalHeroAbsoluteZero_BeginSuppressLeave();
  ShuffleSourceIntoDeck(source);
  ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);
  FusionDuel_SpecialSummonResult(resultId, 1);
  ElementalHeroAbsoluteZero_EndSuppressLeave();
  UpdateDuelGfxExceptField();

  EffectOpt_MarkUsed(THE_GAZE_OF_TIMAEUS);

  {
    u8 col;
    u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id == resultId) {
        TheGazeOfTimaeus_StampSummonedZone(zone);
        break;
      }
    }
  }
  /* ponytail: "Treated as Eye of Timaeus" name checks need a summon-tag outside
   * this file. */
}

void TheGazeOfTimaeus_StampSummonedZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || zone->id == CARD_NONE)
    return;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  sGazeStampRow = fixedRow;
  sGazeStampCol = fixedCol;
  sGazeStampId = zone->id;
  /* Banish during controller's next End Phase (skip this turn's EP). */
  sGazeStampTurnsLeft = 2;
}

void TryApplyTheGazeOfTimaeusEndPhase(void)
{
  struct DuelCard *zone;

  if (sGazeStampTurnsLeft == 0)
    return;

  sGazeStampTurnsLeft--;
  if (sGazeStampTurnsLeft > 0)
    return;

  if (sGazeStampRow > PLAYER_MONSTER_ROW || sGazeStampCol >= MAX_ZONES_IN_ROW) {
    sGazeStampRow = 0xFF;
    sGazeStampCol = 0xFF;
    sGazeStampId = CARD_NONE;
    return;
  }

  zone = gFixedZones[sGazeStampRow][sGazeStampCol];
  if (zone != NULL && zone->id == sGazeStampId && zone->id != CARD_NONE)
    Duel_BanishZone(zone, TRUE);

  sGazeStampRow = 0xFF;
  sGazeStampCol = 0xFF;
  sGazeStampId = CARD_NONE;
}

static void RunGazeOfTimaeusFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 sourceIdx;
  u16 fusions[EXTRA_DECK_SIZE];
  u8 fusionCount;
  u16 resultId;
  u8 i;

  sourceCount = CollectDmDmgSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  sourceIdx = 0xFF;
  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    u8 eligible[FUSION_MAX_SOURCES];
    struct FusionMaterialSource eligibleSources[FUSION_MAX_SOURCES];
    u8 eligibleCount = 0;

    for (i = 0; i < sourceCount; i++) {
      if (BuildMentionFusionTargets(sources[i].cardId, fusions, EXTRA_DECK_SIZE) == 0)
        continue;
      eligible[eligibleCount] = i;
      eligibleSources[eligibleCount] = sources[i];
      eligibleCount++;
    }

    if (eligibleCount == 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    sourceIdx = PlayerPickSourceIndex(eligibleSources, eligibleCount);
    if (sourceIdx == 0xFF)
      return;
    sourceIdx = eligible[sourceIdx];
  } else {
    for (i = 0; i < sourceCount; i++) {
      if (BuildMentionFusionTargets(sources[i].cardId, fusions, EXTRA_DECK_SIZE) > 0) {
        sourceIdx = i;
        break;
      }
    }
    if (sourceIdx == 0xFF) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }
  }

  fusionCount = BuildMentionFusionTargets(sources[sourceIdx].cardId, fusions, EXTRA_DECK_SIZE);
  if (fusionCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    resultId = PlayerPickFusionResult(fusions, fusionCount);
  else
    resultId = AiPickFusionResult(fusions, fusionCount);

  if (resultId == CARD_NONE)
    return;

  ExecuteGazeFusion(&sources[sourceIdx], resultId);
}

static void THE_GAZE_OF_TIMAEUS_ResolveBody(void)
{
  if (!HasUsableGazeTarget()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(THE_GAZE_OF_TIMAEUS);
  if (IsDuelOver() == TRUE)
    return;

  RunGazeOfTimaeusFlow();
}

APPEND_TEXT void EffectTHE_GAZE_OF_TIMAEUS(void)
{
  if (!HasUsableGazeTarget()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(THE_GAZE_OF_TIMAEUS, THE_GAZE_OF_TIMAEUS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void THE_GAZE_OF_TIMAEUS_SelfCheck(void)
{
  if (!IsDarkMagicianOrGirl(DARK_MAGICIAN))
    while (1)
      ;
  if (!IsDarkMagicianOrGirl(DARK_MAGICIAN_GIRL))
    while (1)
      ;
  if (IsDarkMagicianOrGirl(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!FusionMentionsMaterial(AMULET_DRAGON, DARK_MAGICIAN))
    while (1)
      ;
  if (!FusionMentionsMaterial(DARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT, DARK_MAGICIAN_GIRL))
    while (1)
      ;
  if (FusionMentionsMaterial(AMULET_DRAGON, DARK_MAGICIAN_GIRL))
    while (1)
      ;
}
#endif
