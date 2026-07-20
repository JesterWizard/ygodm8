#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define MELODY_DRAGON_MIN_ATK 3000
#define MELODY_DRAGON_MAX_DEF 2500
#define MELODY_SEARCH_COUNT 2

static const u8 sMelodyPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 AnyHandCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

static u8 IsMelodyDragonSearchTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardHasMonsterType(cardId, TYPE_DRAGON))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.atk >= MELODY_DRAGON_MIN_ATK && gCardInfo.def <= MELODY_DRAGON_MAX_DEF;
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

static s16 FindFirstEligibleDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsMelodyDragonSearchTarget(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 CanActivateMelodyOfAwakeningDragon(void)
{
  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  return FindFirstEligibleDeckIndex(ACTIVE_DUELIST) >= 0;
}

static u8 LoadEligibleDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsMelodyDragonSearchTarget(cardId))
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
  if (!IsMelodyDragonSearchTarget(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  return TRUE;
}

static u8 PickEligibleDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadEligibleDeckMenu(turnDuelist, deckIndexMap);
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
          sMelodyPickLabels, ARRAY_COUNT(sMelodyPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static void SearchUpToTwoMelodyDragons(void)
{
  u8 i;

  for (i = 0; i < MELODY_SEARCH_COUNT; i++) {
    u8 deckIndex;

    if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
      break;

    if (FindFirstEligibleDeckIndex(ACTIVE_DUELIST) < 0)
      break;

    deckIndex = PickEligibleDeckIndex(ACTIVE_DUELIST);
    if (deckIndex == 0xFF)
      break;

    if (!AddDeckCardAtIndexToHand(ACTIVE_DUELIST, deckIndex))
      break;
  }
}

static void THE_MELODY_OF_AWAKENING_DRAGON_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(THE_MELODY_OF_AWAKENING_DRAGON);
  if (IsDuelOver() == TRUE || !CanActivateMelodyOfAwakeningDragon())
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, AnyHandCard, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  SearchUpToTwoMelodyDragons();
  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectTHE_MELODY_OF_AWAKENING_DRAGON(void)
{
  if (!CanActivateMelodyOfAwakeningDragon()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(THE_MELODY_OF_AWAKENING_DRAGON,
                                       THE_MELODY_OF_AWAKENING_DRAGON_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MelodyOfAwakeningDragon_SelfCheck(void)
{
  if (!IsMelodyDragonSearchTarget(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (IsMelodyDragonSearchTarget(RED_EYES_B_DRAGON))
    while (1)
      ;
}
#endif
