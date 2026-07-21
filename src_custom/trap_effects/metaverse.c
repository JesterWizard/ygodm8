#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static const u8 sMetaversePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

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

static u8 IsFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  /* Continuous/Field share SPELL_TYPE_INVALID in this engine. */
  return GetSpellType(cardId) == SPELL_TYPE_INVALID;
}

static u8 LoadFieldSpellMenu(u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsFieldSpell(cardId))
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

APPEND_TEXT void EffectMETAVERSE(void)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 pick;
  u16 cardId;
  s8 empty;

  Duel_ShowTrapResponseText(METAVERSE, gTrapEffectData.originCardId);

  menuCount = LoadFieldSpellMenu(deckIndexMap);
  if (menuCount == 0) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  DECKMENU_SAVE();
  if (menuCount == 1 || WhoseTurn() == DUEL_PLAYER) {
    /* Trap controller is INACTIVE during response; for free activation WhoseTurn varies.
     * Default to first / AI pick. */
    pick = 0;
  } else {
    DeckMenu_BeginDuelTrunkView();
    if (!DeckMenuMainPickConfirmWithLabels(sMetaversePickLabels, ARRAY_COUNT(sMetaversePickLabels))) {
      DECKMENU_RESTORE();
      DeckMenu_EndDuelTrunkView();
      pick = 0;
    } else {
      pick = gDeckMenu.currentPos;
      DeckMenu_EndDuelTrunkView();
    }
  }
  cardId = gDeckMenu.cards[pick];
  DECKMENU_RESTORE();

  if (Duel_RemoveDeckCardAt(INACTIVE_DUELIST, deckIndexMap[pick], FALSE) != DUEL_ACTION_OK) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  /* Prefer place as face-up Field on empty backrow; else add to hand. */
  empty = FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_BACKROW]);
  if (empty >= 0 && !Duel_IsBackrowCardOnField(cardId, TRUE)) {
    struct DuelCard *slot = gTurnZones[INACTIVE_DUELIST_BACKROW][empty];

    slot->id = cardId;
    slot->isFaceUp = TRUE;
    slot->isLocked = FALSE;
    slot->isDefending = FALSE;
    slot->unkTwo = 0;
    slot->unkThree = 0;
    slot->unk4 = 0;
    slot->willChangeSides = FALSE;
    ResetPermStage(slot);
    ResetTempStage(slot);
  } else {
    empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
    if (empty >= 0)
      InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
