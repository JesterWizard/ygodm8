#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static const u8 sAmazonessCallPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* ponytail: OPT bit never cleared mid-duel without turn_effect reset hook.
 * Ceiling: blocks 2nd Amazoness Call only until soft-reset / new duel BSS;
 * upgrade: turn_effect Standby → sAmazonessCallUsedThisTurn = 0. */
static u8 sAmazonessCallUsedThisTurn APPEND_DATA = {0};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAmazonessCallSearchTarget(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == AMAZONESS_CALL)
    return FALSE;

  return Duel_IsAmazonessCard(cardId);
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

static s16 FindFirstMatchingDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsAmazonessCallSearchTarget(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 HandHasRoom(void)
{
  return FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0;
}

static u8 CanActivateAmazonessCall(void)
{
  if (sAmazonessCallUsedThisTurn)
    return FALSE;

  return FindFirstMatchingDeckIndex(ACTIVE_DUELIST) >= 0;
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = add to hand, FALSE = send to GY. */
static u8 PlayerChoosesAddToHand(void)
{
  /* ponytail: no dedicated hand/GY choice UI — A = add to hand, B = send to GY.
   * Ceiling: unlabeled buttons; upgrade: effect-text choice menu. */
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

static u8 LoadMatchingDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsAmazonessCallSearchTarget(cardId))
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

static u8 PickMatchingDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadMatchingDeckMenu(turnDuelist, deckIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return 0xFF;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER || gHideEffectText) {
    deckIndex = deckIndexMap[0];
    DECKMENU_RESTORE();
    return deckIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sAmazonessCallPickLabels, ARRAY_COUNT(sAmazonessCallPickLabels))) {
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
  if (!IsAmazonessCallSearchTarget(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone),
                       cardId);
  return TRUE;
}

static u8 SendDeckCardAtIndexToGraveyard(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsAmazonessCallSearchTarget(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  GraveyardExpand_PushTurn(turnDuelist, cardId);
  return TRUE;
}

static void AMAZONESS_CALL_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 deckIndex;
  u8 addToHand;
  s16 autoIndex;

  if (!CanActivateAmazonessCall())
    return;

  Duel_ShowEffectText(AMAZONESS_CALL);

  if (IsDuelOver() == TRUE)
    return;

  deckIndex = PickMatchingDeckIndex(ACTIVE_DUELIST);
  if (deckIndex == 0xFF) {
    autoIndex = FindFirstMatchingDeckIndex(ACTIVE_DUELIST);
    if (autoIndex < 0)
      return;
    deckIndex = (u8)autoIndex;
  }

  if (HandHasRoom()) {
    if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
      addToHand = PlayerChoosesAddToHand();
    else
      addToHand = TRUE; /* AI prefers search to hand */
  } else {
    addToHand = FALSE;
  }

  if (addToHand) {
    if (!AddDeckCardAtIndexToHand(ACTIVE_DUELIST, deckIndex))
      return;
  } else {
    if (!SendDeckCardAtIndexToGraveyard(ACTIVE_DUELIST, deckIndex))
      return;
  }

  sAmazonessCallUsedThisTurn = TRUE;

  if (spellZone != NULL && spellZone->id == AMAZONESS_CALL)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);

  UpdateDuelGfxExceptField();

  /* ponytail: GY banish → target 1 Amazoness you control; that monster can
   * attack all opponent monsters once each, also other monsters cannot attack
   * needs GY ignition + battle multi-attack hooks outside this file.
   * Ceiling: on-field deck search only; upgrade: GY activate → banish
   * AMAZONESS_CALL → PickZone Duel_IsAmazonessCard → mark zone for multi-attack
   * + lock other controlled monsters' attacks until EOT. */
}

APPEND_TEXT void EffectAMAZONESS_CALL(void)
{
  if (!CanActivateAmazonessCall()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(AMAZONESS_CALL, AMAZONESS_CALL_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void AMAZONESS_CALL_SelfCheck(void)
{
  if (!Duel_IsAmazonessCard(AMAZONESS_QUEEN))
    while (1)
      ;
  if (Duel_IsAmazonessCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (IsAmazonessCallSearchTarget(AMAZONESS_CALL))
    while (1)
      ;
  if (!IsAmazonessCallSearchTarget(AMAZONESS_QUEEN))
    while (1)
      ;
}
#endif
