#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static const u8 sAgPickLabels[] APPEND_RODATA = {
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

static u8 IsAncientGearSpellTrapExceptAdvance(u16 cardId)
{
  u8 group;

  if (cardId == CARD_NONE || cardId == ANCIENT_GEAR_ADVANCE)
    return FALSE;

  group = GetTypeGroup(cardId);
  if (group != TYPE_GROUP_SPELL && group != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u8 LoadAgStDeckMenu(u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsAncientGearSpellTrapExceptAdvance(cardId))
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

static void AddDeckCardToHand(u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 empty;
  u16 cardId;
  u8 i;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return;

  empty = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (empty < 0)
    return;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  for (i = deckIndex; i > gDuelDecks[fixedDuelist].cardsDrawn; i--)
    gDuelDecks[fixedDuelist].cards[i] = gDuelDecks[fixedDuelist].cards[i - 1];
  gDuelDecks[fixedDuelist].cardsDrawn++;
  InitHandSlotFromCard(gTurnHands[ACTIVE_DUELIST][empty], cardId);
}

static void SearchAncientGearSpellTrap(void)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 pick;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return;

  menuCount = LoadAgStDeckMenu(deckIndexMap);
  if (menuCount == 0)
    return;

  DECKMENU_SAVE();
  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    pick = 0;
  } else {
    DeckMenu_BeginDuelTrunkView();
    if (!DeckMenuMainPickConfirmWithLabels(sAgPickLabels, ARRAY_COUNT(sAgPickLabels))) {
      DECKMENU_RESTORE();
      DeckMenu_EndDuelTrunkView();
      return;
    }
    pick = gDeckMenu.currentPos;
    DeckMenu_EndDuelTrunkView();
  }
  DECKMENU_RESTORE();
  AddDeckCardToHand(deckIndexMap[pick]);
}

static void ANCIENT_GEAR_ADVANCE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(ANCIENT_GEAR_ADVANCE);
  SearchAncientGearSpellTrap();
  UpdateDuelGfxExceptField();

  /* ponytail: OPT Tribute 1 → draw + tribute-free NS for AGG / Lv5+ that mention
   * it, and cannot-Set this turn need ignition + Normal Summon / Set gates
   * outside this file. Ceiling: activate search only. */
}

APPEND_TEXT void EffectANCIENT_GEAR_ADVANCE(void)
{
  if (Duel_TryResolveSpellThroughTraps(ANCIENT_GEAR_ADVANCE, ANCIENT_GEAR_ADVANCE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
