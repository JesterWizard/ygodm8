#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static const char sKuribohName[] APPEND_RODATA = "Kuriboh";
static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

static const u8 sGenerationNextPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */
static u16 sGenerationNextLockedCardId APPEND_DATA = {CARD_NONE};

u8 GenerationNext_BlocksCardActivation(u16 cardId)
{
  return cardId != CARD_NONE && cardId == sGenerationNextLockedCardId;
}

void GenerationNext_ClearOnTurnBoundary(void)
{
  sGenerationNextLockedCardId = CARD_NONE;
}

static void LockGenerationNextCardActivation(u16 cardId)
{
  sGenerationNextLockedCardId = cardId;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
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

static u16 ActiveLpGap(void)
{
  u16 myLp;
  u16 oppLp;

  if (WhoseTurn() == DUEL_PLAYER) {
    myLp = gDuelLifePoints[DUEL_PLAYER];
    oppLp = gDuelLifePoints[DUEL_OPPONENT];
  } else {
    myLp = gDuelLifePoints[DUEL_OPPONENT];
    oppLp = gDuelLifePoints[DUEL_PLAYER];
  }

  if (myLp >= oppLp)
    return 0;

  return oppLp - myLp;
}

static u8 IsGenerationNextMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (Duel_IsElementalHeroCard(cardId))
    return TRUE;

  if (Duel_CardNameContains(cardId, sKuribohName))
    return TRUE;

  return Duel_CardNameContains(cardId, sNeoSpacianName);
}

static u8 IsGenerationNextTarget(u16 cardId, u16 maxAtk)
{
  if (!IsGenerationNextMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.atk <= maxAtk;
}

static u8 HasEmptyHandSlot(void)
{
  return FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0;
}

static u8 CanSpecialSummonTarget(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

static u8 DeckHasEligible(u8 turnDuelist, u16 maxAtk)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsGenerationNextTarget(gDuelDecks[fixedDuelist].cards[i], maxAtk))
      return TRUE;
  }

  return FALSE;
}

static u8 GyHasEligible(u8 turnDuelist, u16 maxAtk)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 count;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gTurnDuelistBattleState[turnDuelist]->graveyard;

    return IsGenerationNextTarget(top, maxAtk);
  }

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (IsGenerationNextTarget(GraveyardExpand_GetCardAt(fixedDuelist, i), maxAtk))
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateGenerationNext(void)
{
  u16 gap = ActiveLpGap();

  if (EffectOpt_IsUsed(GENERATION_NEXT))
    return FALSE;

  if (gap == 0)
    return FALSE;

  if (!HasEmptyHandSlot() && !CanSpecialSummonTarget())
    return FALSE;

  return DeckHasEligible(ACTIVE_DUELIST, gap) || GyHasEligible(ACTIVE_DUELIST, gap);
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = Deck, FALSE = GY. */
static u8 PlayerChoosesDeck(void)
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

/* TRUE = add to hand, FALSE = Special Summon. */
static u8 PlayerChoosesAddToHand(void)
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

static u8 LoadEligibleDeckMenu(u8 turnDuelist, u16 maxAtk, u8 *deckIndexOut)
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

    if (!IsGenerationNextTarget(cardId, maxAtk))
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

static u8 LoadEligibleGyMenu(u8 fixedDuelist, u16 maxAtk, u8 *gyIndexOut)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsGenerationNextTarget(cardId, maxAtk))
      continue;

    gyIndexOut[menuCount] = i;
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

static s16 PlayerPickDeckIndex(u8 turnDuelist, u16 maxAtk)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadEligibleDeckMenu(turnDuelist, maxAtk, deckIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    deckIndex = deckIndexMap[0];
    DECKMENU_RESTORE();
    return (s16)deckIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sGenerationNextPickLabels,
                                         ARRAY_COUNT(sGenerationNextPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return (s16)deckIndex;
}

static s8 PlayerPickGyIndex(u8 fixedDuelist, u16 maxAtk)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosen;

  DECKMENU_SAVE();

  menuCount = LoadEligibleGyMenu(fixedDuelist, maxAtk, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    chosen = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return chosen;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sGenerationNextPickLabels,
                                         ARRAY_COUNT(sGenerationNextPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosen = (s8)gyIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosen;
}

static u8 AddCardIdToHand(u16 cardId)
{
  s8 handZone;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone),
                       cardId);
  return TRUE;
}

static enum DuelActionResult ResolveFromDeck(u8 deckIndex, u8 addToHand)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;
  struct DuelSummonOpts opts;
  enum DuelActionResult result;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return DUEL_ACTION_NO_TARGET;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
    return DUEL_ACTION_NO_TARGET;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  if (addToHand) {
    if (!AddCardIdToHand(cardId))
      return DUEL_ACTION_NO_ZONE;
    LockGenerationNextCardActivation(cardId);
    return DUEL_ACTION_OK;
  }

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  result = Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
  if (result == DUEL_ACTION_OK)
    LockGenerationNextCardActivation(cardId);
  return result;
}

static enum DuelActionResult ResolveFromGy(u8 gyIndex, u8 addToHand)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;
  struct DuelSummonOpts opts;
  enum DuelActionResult result;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  if (cardId == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  if (addToHand) {
    if (!AddCardIdToHand(cardId))
      return DUEL_ACTION_NO_ZONE;
    LockGenerationNextCardActivation(cardId);
    return DUEL_ACTION_OK;
  }

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  result = Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
  if (result == DUEL_ACTION_OK)
    LockGenerationNextCardActivation(cardId);
  return result;
}

static void GENERATION_NEXT_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u16 gap = ActiveLpGap();
  u8 hasDeck;
  u8 hasGy;
  u8 chooseDeck;
  u8 canHand;
  u8 canSs;
  u8 addToHand;
  s16 deckIndex;
  s8 gyIndex;

  Duel_ShowEffectText(GENERATION_NEXT);

  if (IsDuelOver() == TRUE || !CanActivateGenerationNext())
    return;

  hasDeck = DeckHasEligible(ACTIVE_DUELIST, gap);
  hasGy = GyHasEligible(ACTIVE_DUELIST, gap);

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText && hasDeck && hasGy)
    chooseDeck = PlayerChoosesDeck();
  else if (hasDeck)
    chooseDeck = TRUE;
  else
    chooseDeck = FALSE;

  canHand = HasEmptyHandSlot();
  canSs = CanSpecialSummonTarget();

  if (canHand && canSs) {
    if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
      addToHand = PlayerChoosesAddToHand();
    else
      addToHand = FALSE;
  } else {
    addToHand = canHand;
  }

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  if (chooseDeck) {
    deckIndex = PlayerPickDeckIndex(ACTIVE_DUELIST, gap);
    if (deckIndex < 0)
      return;
    if (ResolveFromDeck((u8)deckIndex, addToHand) == DUEL_ACTION_DUEL_OVER)
      return;
  } else {
    if (!GraveyardExpand_IsEnabled())
      return;
    gyIndex = PlayerPickGyIndex(FixedDuelistForTurnDuelist(ACTIVE_DUELIST), gap);
    if (gyIndex < 0)
      return;
    if (ResolveFromGy((u8)gyIndex, addToHand) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  EffectOpt_MarkUsed(GENERATION_NEXT);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectGENERATION_NEXT(void)
{
  if (!CanActivateGenerationNext()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(GENERATION_NEXT, GENERATION_NEXT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void GENERATION_NEXT_SelfCheck(void)
{
  if (!IsGenerationNextMonster(ELEMENTAL_HERO_SPARKMAN))
    while (1)
      ;
  if (!IsGenerationNextMonster(KURIBOH))
    while (1)
      ;
  if (!IsGenerationNextMonster(NEO_SPACIAN_AQUA_DOLPHIN))
    while (1)
      ;
  if (IsGenerationNextMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!IsGenerationNextTarget(KURIBOH, 300))
    while (1)
      ;
  if (IsGenerationNextTarget(ELEMENTAL_HERO_NEOS, 2000))
    while (1)
      ;
}
#endif
