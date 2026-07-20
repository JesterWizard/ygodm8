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

static const char sArcanaForceArchetypeName[] APPEND_RODATA = "Arcana Force";
static const char sCoinNameNeedle[] APPEND_RODATA = "Coin";

static const u8 sArcanaReadingPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsKnownCoinTossCard(u16 cardId)
{
  switch (cardId) {
  case CUP_OF_ACE:
  case ACE_OF_SWORD:
  case SECOND_COIN_TOSS:
  case ARCANA_SPREAD:
  case TIME_WIZARD:
  case FAIRY_BOX:
  case BLOWBACK_DRAGON:
  case LIGHT_BARRIER:
    return TRUE;
  default:
    return FALSE;
  }
}

static u8 IsCoinTossCardExceptArcanaReading(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == ARCANA_READING)
    return FALSE;

  if (Duel_CardNameContains(cardId, sArcanaForceArchetypeName))
    return TRUE;

  if (Duel_CardNameContains(cardId, sCoinNameNeedle))
    return TRUE;

  return IsKnownCoinTossCard(cardId);
}

static u8 AnyDeckCard(u16 cardId)
{
  return cardId != CARD_NONE;
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

static u8 ActiveControlsFaceUpLightBarrier(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];

    if (zone->id == LIGHT_BARRIER && zone->isFaceUp == TRUE)
      return TRUE;
  }

  return FALSE;
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Returns TRUE for Heads path, FALSE for Tails. */
static u8 PlayerChoosesCoinEffect(void)
{
  /* ponytail: no dedicated choice UI — A = Heads, B = Tails.
   * Ceiling: unlabeled buttons; upgrade path: effect-text choice menu. */
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

static u8 DuelistIsHumanPlayer(u8 turnDuelist)
{
  return FixedDuelistForTurnDuelist(turnDuelist) == DUEL_PLAYER;
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

  if (menuCount == 1 || !DuelistIsHumanPlayer(turnDuelist) || gHideEffectText) {
    deckIndex = deckIndexMap[0];
    DECKMENU_RESTORE();
    return deckIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sArcanaReadingPickLabels, ARRAY_COUNT(sArcanaReadingPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
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

static void ResolveDeckAdd(u8 turnDuelist, u8 (*pred)(u16))
{
  u8 deckIndex;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  deckIndex = PickMatchingDeckIndex(turnDuelist, pred);
  if (deckIndex == 0xFF)
    return;

  AddDeckCardAtIndexToHand(turnDuelist, deckIndex, pred);
  UpdateDuelGfxExceptField();
}

static void ARCANA_READING_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 heads;

  Duel_ShowEffectText(ARCANA_READING);

  if (IsDuelOver() == TRUE)
    return;

  if (ActiveControlsFaceUpLightBarrier() && WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    heads = PlayerChoosesCoinEffect();
  else
    heads = RandRangeU8(0, 1) == 1;

  if (heads)
    ResolveDeckAdd(ACTIVE_DUELIST, IsCoinTossCardExceptArcanaReading);
  else
    ResolveDeckAdd(INACTIVE_DUELIST, AnyDeckCard);

  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);

  /* ponytail: GY banish → Normal Summon 1 Arcana Force needs a GY ignition
   * hook outside this spell file (no in-file graveyard activation path).
   * Ceiling: activation coin effect only; upgrade: GY ignition → banish
   * ARCANA_READING then Duel_NormalSummonFromHand Arcana Force. */
}

APPEND_TEXT void EffectARCANA_READING(void)
{
  if (Duel_TryResolveSpellThroughTraps(ARCANA_READING, ARCANA_READING_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
