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
#include "fusion_destiny.h"
#include "player_decks.h"
#include "spell_effects.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */

#define FUSION_DESTINY_BOARD_CELLS 20
#define FUSION_DESTINY_DESTROY_STAMP_TURNS 2

static u8 sFusionDestinyDestroyStamps[FUSION_DESTINY_BOARD_CELLS] APPEND_DATA = {0};
static u16 sFusionDestinyStampedCardIds[FUSION_DESTINY_BOARD_CELLS] APPEND_DATA = {0};
static u8 sFusionDestinyDarkHeroSpecialSummonLock APPEND_DATA = {0};

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";
static const char sHeroName[] APPEND_RODATA = "HERO";

/* Local recipes that list a Destiny HERO as material.
 * ponytail: incomplete vs printed Destiny Fusion pool (Dystopia, Dangerous,
 * DPE, Dusktopia need archetype / Level-gated wildcards not in fusion_recipes).
 * Ceiling: Destiny End Dragoon only; upgrade: add remaining Destiny HERO Fusion
 * recipes (with Destiny HERO / DARK Effect wildcards) to this table. */
static const struct FusionRecipe sFusionDestinyRecipes[] APPEND_RODATA = {
  { DESTINY_END_DRAGOON, DESTINY_HERO_PLASMA, DESTINY_HERO_DOGMA, 0, 0 },
};

static const u8 sFusionDestinyPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 IsDarkHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_SHADOW && Duel_CardNameContains(cardId, sHeroName);
}

static s8 FusionDestinyBoardCellIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone == NULL || zone < base || zone >= base + FUSION_DESTINY_BOARD_CELLS)
    return -1;

  return (s8)(zone - base);
}

void FusionDestiny_StampSummonedZone(struct DuelCard *zone)
{
  s8 cell = FusionDestinyBoardCellIndex(zone);

  if (cell < 0 || zone->id == CARD_NONE)
    return;

  sFusionDestinyDestroyStamps[cell] = FUSION_DESTINY_DESTROY_STAMP_TURNS;
  sFusionDestinyStampedCardIds[cell] = zone->id;
}

void FusionDestiny_ClearStampedZone(const struct DuelCard *zone)
{
  s8 cell = FusionDestinyBoardCellIndex(zone);

  if (cell < 0)
    return;

  sFusionDestinyDestroyStamps[cell] = 0;
  sFusionDestinyStampedCardIds[cell] = CARD_NONE;
}

void FusionDestiny_MarkDarkHeroSpecialSummonLock(void)
{
  sFusionDestinyDarkHeroSpecialSummonLock = TRUE;
}

void FusionDestiny_ClearDarkHeroSpecialSummonLock(void)
{
  sFusionDestinyDarkHeroSpecialSummonLock = FALSE;
}

u8 FusionDestiny_BlocksSpecialSummon(u16 cardId)
{
  return sFusionDestinyDarkHeroSpecialSummonLock && !IsDarkHeroMonster(cardId);
}

void TryApplyFusionDestinyEndPhase(void)
{
  u8 i;

  for (i = 0; i < FUSION_DESTINY_BOARD_CELLS; i++) {
    struct DuelCard *zone;
    u8 fixedRow;
    u8 fixedCol;

    if (sFusionDestinyDestroyStamps[i] == 0)
      continue;

    zone = &gDuel.board[0][0] + i;
    if (zone->id != sFusionDestinyStampedCardIds[i]) {
      sFusionDestinyDestroyStamps[i] = 0;
      sFusionDestinyStampedCardIds[i] = CARD_NONE;
      continue;
    }

    sFusionDestinyDestroyStamps[i]--;
    if (sFusionDestinyDestroyStamps[i] != 0)
      continue;

    sFusionDestinyStampedCardIds[i] = CARD_NONE;
    if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
      continue;

    Duel_DestroyZone(zone,
                     Duel_TurnDuelistForFixedDuelist(Duel_FixedDuelistForMonsterRow(fixedRow)),
                     TRUE);
    if (IsDuelOver() == TRUE)
      return;
  }
}

static u8 RecipeListsDestinyHero(const struct FusionRecipe *recipe)
{
  u8 i;
  u8 matCount;

  if (recipe == NULL)
    return FALSE;

  SetCardInfo(recipe->result);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  matCount = FusionRecipe_MaterialCount(recipe);
  for (i = 0; i < matCount; i++) {
    u16 mat = FusionRecipe_MaterialAt(recipe, i);

    if (FusionRecipe_MaterialIsConcrete(mat) && IsDestinyHeroMonster(mat))
      return TRUE;
  }

  return FALSE;
}

/* Hand and Deck only (printed Fusion Destiny materials). */
static u8 CollectHandAndDeckSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 i;
  struct FusionMaterialSource deck[FUSION_MAX_SOURCES];
  u8 deckCount;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][i];

    if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;
    if (count >= maxOut)
      break;

    out[count].zone = zone;
    out[count].gyIndex = FUSION_GY_INDEX_NONE;
    out[count].cardId = zone->id;
    count++;
  }

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

  if (!gRuntimeConfig.enable_extra_deck)
    return TRUE;

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

static u8 BuildFeasibleDestinyIndices(const struct FusionMaterialSource *sources,
                                      u8 sourceCount, u8 *outIndices, u8 maxOut)
{
  u8 count = 0;
  u8 i;
  u8 recipeCount = ARRAY_COUNT(sFusionDestinyRecipes);

  for (i = 0; i < recipeCount; i++) {
    const struct FusionRecipe *recipe = &sFusionDestinyRecipes[i];

    if (!RecipeListsDestinyHero(recipe))
      continue;
    if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, sourceCount))
      continue;
    if (!ExtraDeckHasResult(recipe->result))
      continue;
    if (count >= maxOut)
      break;

    outIndices[count++] = i;
  }

  return count;
}

static u8 CanActivateFusionDestiny(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[8];

  if (EffectOpt_IsUsed(FUSION_DESTINY))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  sourceCount = CollectHandAndDeckSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2)
    return FALSE;

  return BuildFeasibleDestinyIndices(sources, sourceCount, feasibleIndices,
                                     ARRAY_COUNT(feasibleIndices))
         > 0;
}

static const struct FusionRecipe *PlayerPickDestinyRecipe(const u8 *recipeIndices, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;
  u8 chosenLocalIdx = 0xFF;

  if (recipeIndices == NULL || count == 0)
    return NULL;

  if (count == 1)
    return &sFusionDestinyRecipes[recipeIndices[0]];

  DECKMENU_SAVE();

  for (j = 0; j < EXPANDED_GRAVEYARD_CAPACITY; j++)
    gDeckMenu.cards[j] = CARD_NONE;

  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = sFusionDestinyRecipes[recipeIndices[j]].result;

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sFusionDestinyPickLabels,
                                         ARRAY_COUNT(sFusionDestinyPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return NULL;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  for (j = 0; j < count; j++) {
    if (sFusionDestinyRecipes[recipeIndices[j]].result == chosenId) {
      chosenLocalIdx = recipeIndices[j];
      break;
    }
  }

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  if (chosenLocalIdx == 0xFF)
    return NULL;

  return &sFusionDestinyRecipes[chosenLocalIdx];
}

static s8 AiPickBestDestinyIndex(const struct FusionMaterialSource *sources, u8 sourceCount)
{
  u8 i;
  u16 bestAtk = 0;
  s8 bestIdx = -1;
  u8 recipeCount = ARRAY_COUNT(sFusionDestinyRecipes);

  for (i = 0; i < recipeCount; i++) {
    const struct FusionRecipe *recipe = &sFusionDestinyRecipes[i];
    u16 candidateAtk;

    if (!RecipeListsDestinyHero(recipe))
      continue;
    if (!FusionRecipe_IsFeasibleWithSources(recipe, sources, sourceCount))
      continue;
    if (!ExtraDeckHasResult(recipe->result))
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

static void PayHandAndDeckMaterials(const struct FusionMaterialSource *selected,
                                    u8 selectedCount)
{
  u8 i;
  u8 milled = FALSE;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone != NULL) {
      ClearZoneAndSendMonToGraveyard(selected[i].zone, ACTIVE_DUELIST);
      continue;
    }

    {
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
      milled = TRUE;
    }
  }

  if (milled)
    Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
}

static void ExecuteFusionDestiny(const struct FusionRecipe *recipe,
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
    Duel_ShowEffectText(FUSION_DESTINY);
    if (IsDuelOver() == TRUE)
      return;
  }

  ElementalHeroAbsoluteZero_BeginSuppressLeave();
  PayHandAndDeckMaterials(selected, selectedCount);
  ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1],
                                 ACTIVE_DUELIST);
  FusionDuel_SpecialSummonResult(recipe->result, selectedCount);
  ElementalHeroAbsoluteZero_EndSuppressLeave();

  FusionDestiny_StampSummonedZone(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone]);
  FusionDestiny_MarkDarkHeroSpecialSummonLock();
  EffectOpt_MarkUsed(FUSION_DESTINY);

  UpdateDuelGfxExceptField();
}

static void RunPlayerFusionDestinyFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[8];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  sourceCount = CollectHandAndDeckSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  feasibleCount = BuildFeasibleDestinyIndices(sources, sourceCount, feasibleIndices,
                                              ARRAY_COUNT(feasibleIndices));
  if (feasibleCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(FUSION_DESTINY);
  if (IsDuelOver() == TRUE)
    return;

  recipe = PlayerPickDestinyRecipe(feasibleIndices, feasibleCount);
  if (recipe == NULL)
    return;

  ExecuteFusionDestiny(recipe, sources, sourceCount, FALSE);
}

static void FUSION_DESTINY_ResolveBody(void)
{
  if (!CanActivateFusionDestiny())
    return;

  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    sourceCount = CollectHandAndDeckSources(sources, FUSION_MAX_SOURCES);
    if (sourceCount < 2) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    bestIdx = AiPickBestDestinyIndex(sources, sourceCount);
    if (bestIdx < 0) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ExecuteFusionDestiny(&sFusionDestinyRecipes[bestIdx], sources, sourceCount, TRUE);
    return;
  }

  RunPlayerFusionDestinyFlow();
}

APPEND_TEXT void EffectFUSION_DESTINY(void)
{
  if (!CanActivateFusionDestiny()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(FUSION_DESTINY, FUSION_DESTINY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void FUSION_DESTINY_SelfCheck(void)
{
  if (!RecipeListsDestinyHero(&sFusionDestinyRecipes[0]))
    while (1)
      ;
  if (!IsDestinyHeroMonster(DESTINY_HERO_PLASMA))
    while (1)
      ;
  if (IsDestinyHeroMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!IsDarkHeroMonster(DESTINY_HERO_PLASMA))
    while (1)
      ;
  if (IsDarkHeroMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
