#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static const u8 sDrillPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

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

static u8 IsAncientGearMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u8 IsSpellCard(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_SPELL;
}

static u8 ControlsAncientGear(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && IsAncientGearMonster(zone->id))
      return TRUE;
  }

  return FALSE;
}

static s16 FindFirstSpellDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsSpellCard(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 HasEmptyBackrow(void)
{
  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]) >= 0;
}

u8 CanActivateANCIENT_GEAR_DRILL(void)
{
  if (!ControlsAncientGear())
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) < 1)
    return FALSE;

  if (!HasEmptyBackrow())
    return FALSE;

  return FindFirstSpellDeckIndex(ACTIVE_DUELIST) >= 0;
}

static void InitSetBackrowSlot(struct DuelCard *zone, u16 cardId)
{
  zone->id = cardId;
  zone->isFaceUp = FALSE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->unkTwo = 0;
  zone->unkThree = 0;
  zone->unk4 = 0;
  zone->willChangeSides = FALSE;
  ResetPermStage(zone);
  ResetTempStage(zone);
}

static u8 LoadSpellDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsSpellCard(cardId))
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

static u8 PickSpellDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadSpellDeckMenu(turnDuelist, deckIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sDrillPickLabels, ARRAY_COUNT(sDrillPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return deckIndex;
}

static u8 SetSpellFromDeckAtIndex(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 backCol;
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  backCol = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (backCol < 0)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsSpellCard(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitSetBackrowSlot(gTurnZones[ACTIVE_DUELIST_BACKROW][backCol], cardId);

  /* ponytail: no per-card same-turn activation lock.
   * Ceiling: Set Spell can still be activated this turn.
   * Upgrade: turn-scoped cardId/zone lock checked at Spell activation. */
  return TRUE;
}

static void DestroyDrillSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == ANCIENT_GEAR_DRILL)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ANCIENT_GEAR_DRILL_ResolveBody(void)
{
  u8 deckIndex;

  Duel_ShowEffectText(ANCIENT_GEAR_DRILL);

  if (IsDuelOver() == TRUE || !CanActivateANCIENT_GEAR_DRILL())
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, AnyHandCard, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  /* Re-check after discard (backrow may still be free; deck may have changed). */
  if (!HasEmptyBackrow() || FindFirstSpellDeckIndex(ACTIVE_DUELIST) < 0) {
    DestroyDrillSpellZone();
    return;
  }

  deckIndex = PickSpellDeckIndex(ACTIVE_DUELIST);
  if (deckIndex == 0xFF) {
    DestroyDrillSpellZone();
    return;
  }

  SetSpellFromDeckAtIndex(ACTIVE_DUELIST, deckIndex);
  DestroyDrillSpellZone();
}

APPEND_TEXT void EffectANCIENT_GEAR_DRILL(void)
{
  if (!CanActivateANCIENT_GEAR_DRILL()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(ANCIENT_GEAR_DRILL, ANCIENT_GEAR_DRILL_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ANCIENT_GEAR_DRILL_SelfCheck(void)
{
  if (!IsAncientGearMonster(ANCIENT_GEAR_GOLEM))
    while (1)
      ;
  if (!IsSpellCard(ANCIENT_GEAR_DRILL))
    while (1)
      ;
  if (IsSpellCard(ANCIENT_GEAR_GOLEM))
    while (1)
      ;
}
#endif
