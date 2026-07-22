#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "elemental_hero_stratos.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void MoveCursorLeft(void);
void MoveCursorRight(void);
void MoveCursorUp(void);
void MoveCursorDown(void);
void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);

extern u16 gNewButtons;
extern u16 gRepeatedOrNewButtons;
extern u16 gPressedButtons;

static const char sHeroArchetypeName[] APPEND_RODATA = "HERO";

static const u8 sStratosPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 IsFaceUpStratosSummon(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_STRATOS)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  /* Attack-position summons stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHeroArchetypeName);
}

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForZone(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return ACTIVE_DUELIST;

  return (turnRow == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 CountOtherHeroMonsters(struct DuelCard *stratosZone)
{
  u8 turnRow;
  u8 col;
  u8 i;
  u8 count = 0;

  if (!Duel_FindTurnMonsterZone(stratosZone, &turnRow, &col))
    return 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[turnRow][i];

    if (zone == NULL || zone == stratosZone || zone->id == CARD_NONE)
      continue;

    if (!IsHeroMonster(zone->id))
      continue;

    if (IsCardFaceUp(zone) || zone->isDefending == FALSE)
      count++;
  }

  return count;
}

static u8 HandHasRoom(u8 turnDuelist)
{
  return FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0;
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

static s16 FindFirstHeroDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsHeroMonster(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 CanSearchHero(u8 turnDuelist)
{
  return HandHasRoom(turnDuelist) && FindFirstHeroDeckIndex(turnDuelist) >= 0;
}

static u8 IsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_BACKROW && fixedRow != PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsSpellOrTrapCard(zone->id);
}

static u8 CountDestroyTargets(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidDestroyTarget(OPPONENT_BACKROW, col))
      count++;
    if (IsValidDestroyTarget(PLAYER_BACKROW, col))
      count++;
  }

  return count;
}

static u8 CanDestroySpellTraps(struct DuelCard *stratosZone)
{
  return CountOtherHeroMonsters(stratosZone) > 0 && CountDestroyTargets() > 0;
}

static u8 LoadHeroDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsHeroMonster(cardId))
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
  if (!IsHeroMonster(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)(handZone)), cardId);
  return TRUE;
}

static u8 PickHeroDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 i;
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadHeroDeckMenu(turnDuelist, deckIndexMap);
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
          sStratosPickLabels, ARRAY_COUNT(sStratosPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static u8 TryAddHeroFromDeck(u8 turnDuelist)
{
  u8 deckIndex;

  if (!CanSearchHero(turnDuelist))
    return FALSE;

  Duel_ShowCardEffectText(ELEMENTAL_HERO_STRATOS,
                          CARD_EFFECT_TEXT_ELEMENTAL_HERO_STRATOS_POPUP_1);
  if (IsDuelOver() == TRUE)
    return TRUE;

  deckIndex = PickHeroDeckIndex(turnDuelist);
  if (deckIndex == 0xFF)
    return FALSE;

  AddDeckCardAtIndexToHand(turnDuelist, deckIndex);
  UpdateDuelGfxExceptField();
  return TRUE;
}

static u8 FindFirstDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidDestroyTarget(OPPONENT_BACKROW, col)) {
      *outRow = OPPONENT_BACKROW;
      *outCol = col;
      return TRUE;
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidDestroyTarget(PLAYER_BACKROW, col)) {
      *outRow = PLAYER_BACKROW;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 GetGraveyardDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void DestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  Duel_DestroyZone(zone, GetGraveyardDuelistForFixedRow(fixedRow), TRUE);
  NotifyDynamicEquipFieldChanged();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Returns: 1 = picked, 0 = cancelled (B), 0xFF = no targets. */
static u8 PickDestroyTarget(u8 *outRow, u8 *outCol)
{
  struct DuelCursor savedCursor = gDuelCursor;
  u8 scrollY;
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstDestroyTarget(&targetRow, &targetCol))
    return 0xFF;

  InitButtonMaps();
  gDuelCursor.currentY = targetRow;
  gDuelCursor.destY = targetRow;
  gDuelCursor.currentX = targetCol;
  gDuelCursor.destX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(savedCursor.currentY, targetRow);

  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    scrollY = gDuelCursor.currentY;
    UpdateFilteredInput_WithRepeat();

    if (gRepeatedOrNewButtons & DPAD_LEFT) {
      MoveCursorLeft();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    } else if (gRepeatedOrNewButtons & DPAD_RIGHT) {
      MoveCursorRight();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    } else if (gRepeatedOrNewButtons & DPAD_UP) {
      MoveCursorUp();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    } else if (gRepeatedOrNewButtons & DPAD_DOWN) {
      MoveCursorDown();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    } else if (gNewButtons & A_BUTTON) {
      if (IsValidDestroyTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
        PlayMusic(SFX_SELECT);
        *outRow = gDuelCursor.currentY;
        *outCol = gDuelCursor.currentX;
        gDuelCursor = savedCursor;
        return 1;
      }
      PlayMusic(SFX_FORBIDDEN);
    } else if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_CANCEL);
      gDuelCursor = savedCursor;
      return 0;
    }

    WaitForVBlank();
  }
}

static void DestroySpellTrapsUpTo(u8 maxCount)
{
  u8 i;

  for (i = 0; i < maxCount; i++) {
    u8 targetRow;
    u8 targetCol;
    u8 pick;

    if (!FindFirstDestroyTarget(&targetRow, &targetCol))
      break;

    if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
      pick = PickDestroyTarget(&targetRow, &targetCol);
      if (pick == 0 || pick == 0xFF)
        break;
    }

    DestroyTarget(targetRow, targetCol);
    if (IsDuelOver() == TRUE)
      return;
  }
}

static u8 TryDestroySpellTraps(struct DuelCard *stratosZone)
{
  u8 maxCount;

  if (!CanDestroySpellTraps(stratosZone))
    return FALSE;

  maxCount = CountOtherHeroMonsters(stratosZone);

  Duel_ShowCardEffectText(ELEMENTAL_HERO_STRATOS,
                          CARD_EFFECT_TEXT_ELEMENTAL_HERO_STRATOS_POPUP_2);
  if (IsDuelOver() == TRUE)
    return TRUE;

  DestroySpellTrapsUpTo(maxCount);
  UpdateDuelGfxExceptField();
  return TRUE;
}

void TryElementalHeroStratosOnMonsterPlacement(struct DuelCard *zone)
{
  u8 turnDuelist;
  u8 canSearch;
  u8 canDestroy;

  if (!IsFaceUpStratosSummon(zone))
    return;

  turnDuelist = TurnDuelistForZone(zone);
  canSearch = CanSearchHero(turnDuelist);
  canDestroy = CanDestroySpellTraps(zone);

  if (!canSearch && !canDestroy)
    return;

  /* On-summon text after field draw so Stratos is visible. */
  UpdateDuelGfxExceptField();

  /* No dedicated A/B choice UI — try search first; player can cancel the deck
   * pick (B) to fall through to destroy when that option is legal. */
  if (canSearch) {
    if (TryAddHeroFromDeck(turnDuelist))
      return;
  }

  if (canDestroy)
    TryDestroySpellTraps(zone);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroStratos_SelfCheck(void)
{
  if (!IsHeroMonster(ELEMENTAL_HERO_SPARKMAN))
    __builtin_trap();

  if (IsHeroMonster(POLYMERIZATION))
    __builtin_trap();

  if (!IsSpellOrTrapCard(POLYMERIZATION))
    __builtin_trap();
}
#endif
