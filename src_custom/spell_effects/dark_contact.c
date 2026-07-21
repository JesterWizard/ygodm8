#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "dark_contact.h"
#include "dark_fusion.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "elemental_hero_absolute_zero.h"
#include "expanded_graveyard.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "removed_from_play.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void ClearZone(struct DuelCard *zone);
void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

enum DarkContactMode {
  DARK_CONTACT_MODE_FUSION = 0,
  DARK_CONTACT_MODE_SEARCH,
};

/* gyIndex bit7 set → Removed-from-play index in low 7 bits; else GY index. */
#define DARK_CONTACT_RFP_FLAG 0x80

static u8 sDarkContactFusionUsed APPEND_DATA = {0};
static u8 sDarkContactSearchUsed APPEND_DATA = {0};

static const u8 sDarkContactPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

void DarkContact_ClearOnTurnBoundary(void)
{
  sDarkContactFusionUsed = FALSE;
  sDarkContactSearchUsed = FALSE;
}

static u8 RecipeIsFiendFusion(const struct FusionRecipe *recipe)
{
  if (recipe == NULL)
    return FALSE;

  return Duel_CardHasMonsterType(recipe->result, TYPE_FIEND);
}

static u8 IsCastleOrDarkFusion(u16 cardId)
{
  return cardId == SUPREME_KINGS_CASTLE || cardId == DARK_FUSION;
}

static u8 HandHasRoomForSearch(void)
{
  return FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0;
}

static s16 FindFirstMatchingDeckIndex(u8 turnDuelist, u8 (*pred)(u16))
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (pred(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 CollectFieldGyAndBanishSources(struct FusionMaterialSource *out, u8 maxOut)
{
  u8 count = 0;
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 gyCount;
  u8 rfpCount;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

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

  if (!RemovedFromPlay_IsEnabled())
    return count;

  rfpCount = RemovedFromPlay_GetCount(fixedDuelist);
  for (i = 0; i < rfpCount; i++) {
    u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);

    if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;
    if (count >= maxOut)
      break;

    out[count].zone = NULL;
    out[count].gyIndex = (u8)(i | DARK_CONTACT_RFP_FLAG);
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

static u8 FusionModeIsAvailable(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;

  if (sDarkContactFusionUsed)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  sourceCount = CollectFieldGyAndBanishSources(sources, FUSION_MAX_SOURCES);
  if (sourceCount < 2)
    return FALSE;

  feasibleCount = FusionDuel_BuildFeasibleRecipeIndices(sources, sourceCount, feasibleIndices,
                                                        ARRAY_COUNT(feasibleIndices),
                                                        RecipeIsFiendFusion);
  if (feasibleCount == 0)
    return FALSE;

  feasibleCount = FilterFeasibleByExtraDeck(feasibleIndices, feasibleCount);
  return feasibleCount > 0;
}

static u8 SearchModeIsAvailable(void)
{
  if (sDarkContactSearchUsed)
    return FALSE;

  if (!HandHasRoomForSearch())
    return FALSE;

  return FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsCastleOrDarkFusion) >= 0;
}

static u8 CanActivateDarkContact(void)
{
  return FusionModeIsAvailable() || SearchModeIsAvailable();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* A = Fusion; B = search Castle/Dark Fusion. */
static u8 PlayerChoosesDarkContactMode(void)
{
  u8 hasFusion = FusionModeIsAvailable();
  u8 hasSearch = SearchModeIsAvailable();

  if (hasFusion && !hasSearch)
    return DARK_CONTACT_MODE_FUSION;
  if (hasSearch && !hasFusion)
    return DARK_CONTACT_MODE_SEARCH;

  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return DARK_CONTACT_MODE_FUSION;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return DARK_CONTACT_MODE_SEARCH;
    }

    WaitForVBlank();
  }
}

static u8 AiPickDarkContactMode(void)
{
  if (FusionModeIsAvailable())
    return DARK_CONTACT_MODE_FUSION;
  return DARK_CONTACT_MODE_SEARCH;
}

static u8 LoadMatchingDeckMenu(u8 turnDuelist, u8 (*pred)(u16), u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!pred(cardId))
      continue;

    deckIndexOut[menuCount] = i;
    gDeckMenu.cards[menuCount] = cardId;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static u8 PickMatchingDeckIndex(u8 turnDuelist, u8 (*pred)(u16))
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadMatchingDeckMenu(turnDuelist, pred, deckIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return 0xFF;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    deckIndex = deckIndexMap[0];
    DECKMENU_RESTORE();
    return deckIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sDarkContactPickLabels,
                                         ARRAY_COUNT(sDarkContactPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 AddDeckCardAtIndexToHand(u8 turnDuelist, u8 deckIndex, u8 (*pred)(u16))
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!pred(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone),
                       cardId);
  return TRUE;
}

static void ResolveSearch(void)
{
  u8 deckIndex;

  deckIndex = PickMatchingDeckIndex(ACTIVE_DUELIST, IsCastleOrDarkFusion);
  if (deckIndex == 0xFF) {
    s16 autoIndex = FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsCastleOrDarkFusion);

    if (autoIndex < 0)
      return;
    deckIndex = (u8)autoIndex;
  }

  if (AddDeckCardAtIndexToHand(ACTIVE_DUELIST, deckIndex, IsCastleOrDarkFusion))
    sDarkContactSearchUsed = TRUE;
}

static void RemoveBanishedAt(u8 fixedDuelist, u8 index)
{
  RemovedFromPlay_RemoveAt(fixedDuelist, index);
}

static void ReturnCardToDeck(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static void PayDarkContactShuffleMaterials(const struct FusionMaterialSource *selected,
                                           u8 selectedCount)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 gyIndices[FUSION_MAX_MATERIALS];
  u8 rfpIndices[FUSION_MAX_MATERIALS];
  u8 gyCount = 0;
  u8 rfpCount = 0;
  u8 i;
  u8 g;

  for (i = 0; i < selectedCount; i++) {
    if (selected[i].zone != NULL) {
      u16 cardId = selected[i].zone->id;

      ClearZone(selected[i].zone);
      ReturnCardToDeck(ACTIVE_DUELIST, cardId);
    } else if (selected[i].gyIndex != FUSION_GY_INDEX_NONE) {
      if (selected[i].gyIndex & DARK_CONTACT_RFP_FLAG)
        rfpIndices[rfpCount++] = (u8)(selected[i].gyIndex & ~DARK_CONTACT_RFP_FLAG);
      else
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

  while (rfpCount > 0) {
    u8 best = 0;

    for (g = 1; g < rfpCount; g++) {
      if (rfpIndices[g] > rfpIndices[best])
        best = g;
    }

    {
      u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, rfpIndices[best]);

      RemoveBanishedAt(fixedDuelist, rfpIndices[best]);
      ReturnCardToDeck(ACTIVE_DUELIST, cardId);
    }

    rfpIndices[best] = rfpIndices[rfpCount - 1];
    rfpCount--;
  }

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
}

static void ExecuteDarkContactFusion(const struct FusionRecipe *recipe,
                                     const struct FusionMaterialSource *sources,
                                     u8 sourceCount, u8 showEffectText)
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
    Duel_ShowEffectText(DARK_CONTACT);
    if (IsDuelOver() == TRUE)
      return;
  }

  ElementalHeroAbsoluteZero_BeginSuppressLeave();
  PayDarkContactShuffleMaterials(selected, selectedCount);
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);
  FusionDuel_SpecialSummonResult(recipe->result, selectedCount);
  ElementalHeroAbsoluteZero_EndSuppressLeave();
  UpdateDuelGfxExceptField();
  sDarkContactFusionUsed = TRUE;

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

static void RunPlayerDarkContactFusionFlow(void)
{
  struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
  u8 sourceCount;
  u8 feasibleIndices[32];
  u8 feasibleCount;
  const struct FusionRecipe *recipe;

  sourceCount = CollectFieldGyAndBanishSources(sources, FUSION_MAX_SOURCES);
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
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  recipe = FusionDuel_PlayerConfirmFusionPick(feasibleIndices, feasibleCount);
  if (recipe == NULL)
    return;

  ExecuteDarkContactFusion(recipe, sources, sourceCount, FALSE);
}

static void ResolveFusion(void)
{
  if (WhoseTurn() != DUEL_PLAYER) {
    struct FusionMaterialSource sources[FUSION_MAX_SOURCES];
    u8 sourceCount;
    s8 bestIdx;

    sourceCount = CollectFieldGyAndBanishSources(sources, FUSION_MAX_SOURCES);
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

    ExecuteDarkContactFusion(&gFusionRecipes[bestIdx], sources, sourceCount, FALSE);
    return;
  }

  RunPlayerDarkContactFusionFlow();
}

static void DARK_CONTACT_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 mode;

  if (!CanActivateDarkContact()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(DARK_CONTACT);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    mode = PlayerChoosesDarkContactMode();
  else
    mode = AiPickDarkContactMode();

  if (mode == DARK_CONTACT_MODE_FUSION && !FusionModeIsAvailable()) {
    if (SearchModeIsAvailable())
      mode = DARK_CONTACT_MODE_SEARCH;
    else
      return;
  } else if (mode == DARK_CONTACT_MODE_SEARCH && !SearchModeIsAvailable()) {
    if (FusionModeIsAvailable())
      mode = DARK_CONTACT_MODE_FUSION;
    else
      return;
  }

  if (mode == DARK_CONTACT_MODE_SEARCH) {
    ResolveSearch();
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
    UpdateDuelGfxExceptField();
    return;
  }

  ResolveFusion();
}

APPEND_TEXT void EffectDARK_CONTACT(void)
{
  if (!CanActivateDarkContact()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DARK_CONTACT, DARK_CONTACT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DARK_CONTACT_SelfCheck(void)
{
  if (!IsCastleOrDarkFusion(SUPREME_KINGS_CASTLE))
    while (1)
      ;
  if (!IsCastleOrDarkFusion(DARK_FUSION))
    while (1)
      ;
  if (IsCastleOrDarkFusion(POLYMERIZATION))
    while (1)
      ;
  if (!Duel_CardHasMonsterType(EVIL_HERO_INFERNO_WING, TYPE_FIEND))
    while (1)
      ;
}
#endif
