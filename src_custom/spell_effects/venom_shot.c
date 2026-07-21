#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

#define VENOM_SHOT_COUNTERS 2

void UpdateDuelGfxExceptField(void);

static const char sVenomArchetypeName[] APPEND_RODATA = "Venom";

static const u8 sVenomShotPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 InactiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsVenomOrVennominBoss(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES
      || cardId == VENNOMINON_THE_KING_OF_POISONOUS_SNAKES)
    return TRUE;

  return Duel_CardNameContains(cardId, sVenomArchetypeName);
}

static u8 IsReptileMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_REPTILE);
}

static u8 ControlsFaceUpVenomBoss(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (!MonsterIsFaceUp(zone))
      continue;

    if (IsVenomOrVennominBoss(zone->id))
      return TRUE;
  }

  return FALSE;
}

static u8 DeckHasReptile(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsReptileMonster(gDuelDecks[fixedDuelist].cards[i]))
      return TRUE;
  }

  return FALSE;
}

static u8 IsValidVenomShotOppTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != InactiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return MonsterIsFaceUp(zone);
}

static u8 HasVenomShotOppTarget(void)
{
  u8 col;
  u8 row = InactiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidVenomShotOppTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static s16 FindFirstReptileDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsReptileMonster(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 LoadReptileDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsReptileMonster(cardId))
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

static u8 SendDeckCardAtIndexToGraveyard(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsReptileMonster(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  GraveyardExpand_PushTurn(turnDuelist, cardId);
  return TRUE;
}

static u8 PickReptileDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadReptileDeckMenu(turnDuelist, deckIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sVenomShotPickLabels,
                                         ARRAY_COUNT(sVenomShotPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

u8 CanActivateVENOM_SHOT(void)
{
  return ControlsFaceUpVenomBoss() && DeckHasReptile(ACTIVE_DUELIST) && HasVenomShotOppTarget();
}

static void DestroyVenomShotSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == VENOM_SHOT)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ResolveVenomShotOppTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidVenomShotOppTarget(fixedRow, fixedCol))
    return;

  /* 2 Venom Counters ≈ −2 stages (~−1000 ATK); EP destroy-at-0 via Venom Swamp. */
  {
    u8 i;

    for (i = 0; i < VENOM_SHOT_COUNTERS; i++)
      DecrementPermStage(zone);
  }
  Duel_RefreshMonsterStatOverlays();

  DestroyVenomShotSpellZone();
}

static void CancelVenomShotTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyVenomShotSpellZone();
}

static u8 AiPickVenomShotOppTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = InactiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidVenomShotOppTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void VENOM_SHOT_ResolveBody(void)
{
  u8 deckIndex;

  Duel_ShowEffectText(VENOM_SHOT);

  if (IsDuelOver() == TRUE || !CanActivateVENOM_SHOT())
    return;

  if (FindFirstReptileDeckIndex(ACTIVE_DUELIST) < 0)
    return;

  deckIndex = PickReptileDeckIndex(ACTIVE_DUELIST);
  if (deckIndex == 0xFF) {
    DestroyVenomShotSpellZone();
    return;
  }

  if (!SendDeckCardAtIndexToGraveyard(ACTIVE_DUELIST, deckIndex)) {
    DestroyVenomShotSpellZone();
    return;
  }

  if (IsDuelOver() == TRUE)
    return;

  if (!HasVenomShotOppTarget()) {
    DestroyVenomShotSpellZone();
    return;
  }

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidVenomShotOppTarget, ResolveVenomShotOppTarget,
                     CancelVenomShotTargeting, AiPickVenomShotOppTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectVENOM_SHOT(void)
{
  if (!CanActivateVENOM_SHOT()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(VENOM_SHOT, VENOM_SHOT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void VenomShot_SelfCheck(void)
{
  if (!IsVenomOrVennominBoss(VENOM_SNAKE))
    while (1)
      ;
  if (!IsVenomOrVennominBoss(VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES))
    while (1)
      ;
  if (IsVenomOrVennominBoss(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!IsReptileMonster(VENOM_SNAKE))
    while (1)
      ;
}
#endif
