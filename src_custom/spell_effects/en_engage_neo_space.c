#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void IncrementPermStage(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

static const u8 sEnEngagePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 sEnEngageUsedThisTurn APPEND_DATA = {0};

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

static u8 IsNeoSpacianMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sNeoSpacianName);
}

static u8 IsElementalHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_IsElementalHeroCard(cardId);
}

static u8 IsEngageSummonTarget(u16 cardId)
{
  if (IsNeoSpacianMonster(cardId))
    return TRUE;

  if (!IsElementalHeroMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 5;
}

static u8 HandHasMatching(u8 (*pred)(u16))
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (pred(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static s16 FindDeckMatching(u8 (*pred)(u16))
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (pred(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static s8 PickHandMatching(u8 (*pred)(u16))
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], pred);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (pred(gTurnHands[ACTIVE_DUELIST][i]->id))
      return (s8)i;
  }

  return -1;
}

static u8 MillDeckMatching(u8 (*pred)(u16))
{
  s16 deckIndex = FindDeckMatching(pred);
  u8 fixedDuelist;
  u16 cardId;

  if (deckIndex < 0)
    return FALSE;

  fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
  return TRUE;
}

static u8 LoadEngageSummonMenu(u8 *deckIndexOut)
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

    if (!IsEngageSummonTarget(cardId))
      continue;
    if (Duel_CardCannotBeSpecialSummoned(cardId))
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

static void AddPolymerization(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  s8 empty;
  u8 i;
  u16 cardId = CARD_NONE;

  empty = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (empty < 0)
    return;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == POLYMERIZATION) {
      if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, i, FALSE) != DUEL_ACTION_OK)
        return;
      cardId = POLYMERIZATION;
      break;
    }
  }

  if (cardId == CARD_NONE) {
    if (GraveyardExpand_IsEnabled()) {
      u8 count = GraveyardExpand_GetCount(fixedDuelist);

      for (i = 0; i < count; i++) {
        if (GraveyardExpand_GetCardAt(fixedDuelist, i) == POLYMERIZATION) {
          cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
          break;
        }
      }
    } else if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == POLYMERIZATION) {
      cardId = POLYMERIZATION;
      gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard = CARD_NONE;
    }
  }

  if (cardId != CARD_NONE)
    InitHandSlotFromCard(gTurnHands[ACTIVE_DUELIST][empty], cardId);
}

u8 CanActivateEN_ENGAGE_NEO_SPACE(void)
{
  if (sEnEngageUsedThisTurn)
    return FALSE;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;
  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;
  if (FindDeckMatching(IsEngageSummonTarget) < 0)
    return FALSE;

  if (HandHasMatching(IsNeoSpacianMonster) && FindDeckMatching(IsElementalHeroMonster) >= 0)
    return TRUE;
  if (HandHasMatching(IsElementalHeroMonster) && FindDeckMatching(IsNeoSpacianMonster) >= 0)
    return TRUE;

  return FALSE;
}

static void EN_ENGAGE_NEO_SPACE_ResolveBody(void)
{
  s8 handZone;
  u8 handIsNeo;
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 pick;
  u16 summonId;
  struct DuelSummonOpts opts;
  u8 col;

  if (!CanActivateEN_ENGAGE_NEO_SPACE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(EN_ENGAGE_NEO_SPACE);
  if (IsDuelOver() == TRUE)
    return;

  if (HandHasMatching(IsNeoSpacianMonster) && FindDeckMatching(IsElementalHeroMonster) >= 0) {
    handZone = PickHandMatching(IsNeoSpacianMonster);
    handIsNeo = TRUE;
  } else {
    handZone = PickHandMatching(IsElementalHeroMonster);
    handIsNeo = FALSE;
  }

  if (handZone < 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  ClearZoneAndSendMonToGraveyard(gTurnHands[ACTIVE_DUELIST][handZone], ACTIVE_DUELIST);

  if (handIsNeo) {
    if (!MillDeckMatching(IsElementalHeroMonster)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }
  } else if (!MillDeckMatching(IsNeoSpacianMonster)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  menuCount = LoadEngageSummonMenu(deckIndexMap);
  if (menuCount == 0) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  DECKMENU_SAVE();
  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    pick = 0;
  } else {
    DeckMenu_BeginDuelTrunkView();
    if (!DeckMenuMainPickConfirmWithLabels(sEnEngagePickLabels, ARRAY_COUNT(sEnEngagePickLabels))) {
      DECKMENU_RESTORE();
      DeckMenu_EndDuelTrunkView();
      return;
    }
    pick = gDeckMenu.currentPos;
    DeckMenu_EndDuelTrunkView();
  }
  DECKMENU_RESTORE();

  summonId = gDuelDecks[FixedDuelistForTurnDuelist(ACTIVE_DUELIST)].cards[deckIndexMap[pick]];
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, summonId, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  if (summonId == ELEMENTAL_HERO_NEOS) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *z = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

      if (z != NULL && z->id == ELEMENTAL_HERO_NEOS) {
        /* ponytail: 1 stage ~= 500 ATK so +2 ≈ +1000. */
        IncrementPermStage(z);
        IncrementPermStage(z);
        break;
      }
    }
  }

  AddPolymerization();
  sEnEngageUsedThisTurn = TRUE;
  UpdateDuelGfxExceptField();

  /* ponytail: ED Fusion-only SS lock this turn needs SpecialSummon gate outside
   * this file. Ceiling: no lock; upgrade: turn flag → ED non-Fusion blocked. */
}

APPEND_TEXT void EffectEN_ENGAGE_NEO_SPACE(void)
{
  if (Duel_TryResolveSpellThroughTraps(EN_ENGAGE_NEO_SPACE, EN_ENGAGE_NEO_SPACE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
