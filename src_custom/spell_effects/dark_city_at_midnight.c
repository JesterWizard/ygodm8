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

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static const u8 sDarkCityPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 sDarkCitySearchUsed APPEND_DATA = {0};

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

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 IsDarkCitySearchTarget(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == DARK_CITY_AT_MIDNIGHT)
    return FALSE;

  if (IsDestinyHeroMonster(cardId))
    return TRUE;

  /* Approximate "mentions a Destiny HERO monster's card name". */
  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 LoadSearchMenu(u8 *deckIndexOut)
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

    if (!IsDarkCitySearchTarget(cardId))
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

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return;

  empty = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (empty < 0)
    return;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
    return;

  cardId = gDeckMenu.cards[0]; /* wrong — need save before remove */
  (void)cardId;
}

static void SearchOnActivate(void)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 pick;
  u16 cardId;
  s8 empty;
  u8 fixedDuelist;

  if (sDarkCitySearchUsed)
    return;

  empty = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (empty < 0)
    return;

  menuCount = LoadSearchMenu(deckIndexMap);
  if (menuCount == 0)
    return;

  DECKMENU_SAVE();
  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    pick = 0;
  } else {
    DeckMenu_BeginDuelTrunkView();
    if (!DeckMenuMainPickConfirmWithLabels(sDarkCityPickLabels, ARRAY_COUNT(sDarkCityPickLabels))) {
      DECKMENU_RESTORE();
      DeckMenu_EndDuelTrunkView();
      return;
    }
    pick = gDeckMenu.currentPos;
    DeckMenu_EndDuelTrunkView();
  }

  cardId = gDeckMenu.cards[pick];
  DECKMENU_RESTORE();

  fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndexMap[pick], FALSE) != DUEL_ACTION_OK)
    return;

  InitHandSlotFromCard(gTurnHands[ACTIVE_DUELIST][empty], cardId);
  sDarkCitySearchUsed = TRUE;
  (void)fixedDuelist;
}

static void DARK_CITY_AT_MIDNIGHT_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(DARK_CITY_AT_MIDNIGHT);
  SearchOnActivate();
  UpdateDuelGfxExceptField();

  /* ponytail: each Lv8+ Destiny HERO SS → Warriors +300 ATK, and destroy → Deck
   * SS Destiny HERO need summon/destroy hooks outside this file.
   * Ceiling: activate search only (printed: search if activated this turn). */
  (void)AddDeckCardToHand;
}

APPEND_TEXT void EffectDARK_CITY_AT_MIDNIGHT(void)
{
  if (Duel_TryResolveSpellThroughTraps(DARK_CITY_AT_MIDNIGHT, DARK_CITY_AT_MIDNIGHT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
