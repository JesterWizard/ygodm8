#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define SUMMONERS_ART_MIN_LEVEL 5

void UpdateDuelGfxExceptField(void);

static const u8 sSummonersArtPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLevel5OrHigherNormalMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != COLOR_NORMAL)
    return FALSE;

  return gCardInfo.level >= SUMMONERS_ART_MIN_LEVEL;
}

static u8 CountEmptyHandSlots(u8 turnDuelist)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[turnDuelist][i]->id == CARD_NONE)
      count++;
  }

  return count;
}

static u8 HandHasRoomForDeckSearch(u8 turnDuelist)
{
  u8 i;

  if (CountEmptyHandSlots(turnDuelist) > 0)
    return TRUE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[turnDuelist][i]->id == SUMMONERS_ART)
      return TRUE;
  }

  return FALSE;
}

static s16 FindFirstEligibleDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsLevel5OrHigherNormalMonster(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

u8 CanActivateSUMMONERS_ART(void)
{
  if (!HandHasRoomForDeckSearch(ACTIVE_DUELIST))
    return FALSE;

  return FindFirstEligibleDeckIndex(ACTIVE_DUELIST) >= 0;
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

    if (!IsLevel5OrHigherNormalMonster(cardId))
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
          sSummonersArtPickLabels, ARRAY_COUNT(sSummonersArtPickLabels))) {
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
  if (!IsLevel5OrHigherNormalMonster(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  return TRUE;
}

static void SUMMONERS_ART_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 deckIndex;

  Duel_ShowEffectText(SUMMONERS_ART);
  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (FindFirstEligibleDeckIndex(ACTIVE_DUELIST) < 0)
    return;

  deckIndex = PickEligibleDeckIndex(ACTIVE_DUELIST);
  if (deckIndex != 0xFF)
    AddDeckCardAtIndexToHand(ACTIVE_DUELIST, deckIndex);

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectSUMMONERS_ART(void)
{
  if (!CanActivateSUMMONERS_ART()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(SUMMONERS_ART, SUMMONERS_ART_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void SUMMONERS_ART_SelfCheck(void)
{
  if (!IsLevel5OrHigherNormalMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (IsLevel5OrHigherNormalMonster(BABY_DRAGON))
    while (1)
      ;
}
#endif
