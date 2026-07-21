#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static const char sGravekeeperArchetypeName[] APPEND_RODATA = "Gravekeeper";

static const u8 sNecrovalleyThronePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsGravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGravekeeperArchetypeName);
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

static u8 HandHasRoomForDeckSearch(u8 turnDuelist)
{
  u8 i;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0)
    return TRUE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[turnDuelist][i]->id == NECROVALLEY_THRONE)
      return TRUE;
  }

  return FALSE;
}

static s16 FindFirstGravekeeperDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsGravekeeperMonster(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 HandHasGravekeeper(u8 turnDuelist)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsGravekeeperMonster(gTurnHands[turnDuelist][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 CanSearchGravekeeper(void)
{
  if (!HandHasRoomForDeckSearch(ACTIVE_DUELIST))
    return FALSE;

  return FindFirstGravekeeperDeckIndex(ACTIVE_DUELIST) >= 0;
}

static u8 CanNormalSummonGravekeeper(void)
{
  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HandHasGravekeeper(ACTIVE_DUELIST);
}

u8 CanActivateNECROVALLEY_THRONE(void)
{
  return !EffectOpt_IsUsed(NECROVALLEY_THRONE)
         && (CanSearchGravekeeper() || CanNormalSummonGravekeeper());
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Returns TRUE for deck search, FALSE for Normal Summon. */
static u8 PlayerChoosesDeckSearch(void)
{
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return TRUE;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return FALSE;
    }

    WaitForVBlank();
  }
}

static u8 LoadGravekeeperDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsGravekeeperMonster(cardId))
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

static u8 PickGravekeeperDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadGravekeeperDeckMenu(turnDuelist, deckIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(
          sNecrovalleyThronePickLabels, ARRAY_COUNT(sNecrovalleyThronePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static u8 AddDeckCardAtIndexToHand(u8 turnDuelist, u8 deckIndex)
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
  if (!IsGravekeeperMonster(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  return TRUE;
}

static void ResolveGravekeeperSearch(void)
{
  u8 deckIndex;

  if (FindFirstGravekeeperDeckIndex(ACTIVE_DUELIST) < 0)
    return;

  deckIndex = PickGravekeeperDeckIndex(ACTIVE_DUELIST);
  if (deckIndex != 0xFF)
    AddDeckCardAtIndexToHand(ACTIVE_DUELIST, deckIndex);
}

static void ResolveGravekeeperNormalSummon(void)
{
  struct DuelSummonOpts opts = Duel_DefaultNormalSummonOpts(TRUE);
  u8 savedBlocked = gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked;

  /* Allow the Throne's granted Normal Summon even if NS was already used. */
  gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked = 0;

  if (Duel_NormalSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsGravekeeperMonster, opts)
      != DUEL_ACTION_OK)
    gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked = savedBlocked;
}

static void NECROVALLEY_THRONE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 chooseSearch;
  u8 hasSearch;
  u8 hasSummon;

  Duel_ShowEffectText(NECROVALLEY_THRONE);

  if (IsDuelOver() == TRUE || !CanActivateNECROVALLEY_THRONE())
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  hasSearch = CanSearchGravekeeper();
  hasSummon = CanNormalSummonGravekeeper();

  if (!hasSearch && !hasSummon)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText && hasSearch && hasSummon)
    chooseSearch = PlayerChoosesDeckSearch();
  else if (hasSearch)
    chooseSearch = TRUE;
  else
    chooseSearch = FALSE;

  if (chooseSearch)
    ResolveGravekeeperSearch();
  else
    ResolveGravekeeperNormalSummon();

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectNECROVALLEY_THRONE(void)
{
  if (!CanActivateNECROVALLEY_THRONE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  EffectOpt_MarkUsed(NECROVALLEY_THRONE);
  if (Duel_TryResolveSpellThroughTraps(NECROVALLEY_THRONE, NECROVALLEY_THRONE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void NECROVALLEY_THRONE_SelfCheck(void)
{
  if (!IsGravekeeperMonster(GRAVEKEEPERS_SPY))
    while (1)
      ;
  if (IsGravekeeperMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
