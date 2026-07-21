#include "global.h"
#include "common-chax.h"
#include "amazoness_call.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"
#include "the_dark_door.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

extern u8 gAmazonessCallMultiAttackActive;
extern u8 gAmazonessCallMultiAttackAnchorRow;
extern u8 gAmazonessCallMultiAttackAnchorCol;
extern u8 gAmazonessCallMultiAttackedMask;

#define AMAZONESS_CALL_ZONE_NONE 0xFF

static const u8 sAmazonessCallPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* OPT via EffectOpt_* — cleared on turn boundary (Phase 3 EffectEvent_OnTurnBoundary). */

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAmazonessCallSearchTarget(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == AMAZONESS_CALL)
    return FALSE;

  return Duel_IsAmazonessCard(cardId);
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

static s16 FindFirstMatchingDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsAmazonessCallSearchTarget(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 HandHasRoom(void)
{
  return FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0;
}

static u8 CanActivateAmazonessCall(void)
{
  if (EffectOpt_IsUsed(AMAZONESS_CALL))
    return FALSE;

  return FindFirstMatchingDeckIndex(ACTIVE_DUELIST) >= 0;
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = add to hand, FALSE = send to GY.
 * A = add to hand, B = send to GY (no labeled choice menu). */
static u8 PlayerChoosesAddToHand(void)
{
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

static u8 LoadMatchingDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsAmazonessCallSearchTarget(cardId))
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

static u8 PickMatchingDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadMatchingDeckMenu(turnDuelist, deckIndexMap);
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
          sAmazonessCallPickLabels, ARRAY_COUNT(sAmazonessCallPickLabels))) {
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
  if (!IsAmazonessCallSearchTarget(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone),
                       cardId);
  return TRUE;
}

static u8 SendDeckCardAtIndexToGraveyard(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsAmazonessCallSearchTarget(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  GraveyardExpand_PushTurn(turnDuelist, cardId);
  return TRUE;
}

static void AMAZONESS_CALL_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 deckIndex;
  u8 addToHand;
  s16 autoIndex;

  if (!CanActivateAmazonessCall())
    return;

  Duel_ShowEffectText(AMAZONESS_CALL);

  if (IsDuelOver() == TRUE)
    return;

  deckIndex = PickMatchingDeckIndex(ACTIVE_DUELIST);
  if (deckIndex == 0xFF) {
    autoIndex = FindFirstMatchingDeckIndex(ACTIVE_DUELIST);
    if (autoIndex < 0)
      return;
    deckIndex = (u8)autoIndex;
  }

  if (HandHasRoom()) {
    if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
      addToHand = PlayerChoosesAddToHand();
    else
      addToHand = TRUE; /* AI prefers search to hand */
  } else {
    addToHand = FALSE;
  }

  if (addToHand) {
    if (!AddDeckCardAtIndexToHand(ACTIVE_DUELIST, deckIndex))
      return;
  } else {
    if (!SendDeckCardAtIndexToGraveyard(ACTIVE_DUELIST, deckIndex))
      return;
  }

  EffectOpt_MarkUsed(AMAZONESS_CALL);

  if (spellZone != NULL && spellZone->id == AMAZONESS_CALL)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);

  UpdateDuelGfxExceptField();
}

void ClearAmazonessCallMultiAttackState(void)
{
  gAmazonessCallMultiAttackActive = FALSE;
  gAmazonessCallMultiAttackAnchorRow = AMAZONESS_CALL_ZONE_NONE;
  gAmazonessCallMultiAttackAnchorCol = AMAZONESS_CALL_ZONE_NONE;
  gAmazonessCallMultiAttackedMask = 0;
}

static u8 OpponentMonsterTurnRow(void)
{
  return WhoseTurn() == DUEL_PLAYER
      ? INACTIVE_DUELIST_MONSTER_ROW
      : ACTIVE_DUELIST_MONSTER_ROW;
}

static u8 HasUnattackedOpponentMonster(void)
{
  u8 row = OpponentMonsterTurnRow();
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[row][col]->id == CARD_NONE)
      continue;

    if ((gAmazonessCallMultiAttackedMask & (1u << col)) == 0)
      return TRUE;
  }

  return FALSE;
}

static u8 AttackerIsCallMultiAttackAnchor(struct DuelCard *attacker)
{
  u8 turnRow;
  u8 col;

  if (!gAmazonessCallMultiAttackActive || attacker == NULL)
    return FALSE;

  if (gAmazonessCallMultiAttackAnchorRow == AMAZONESS_CALL_ZONE_NONE)
    return FALSE;

  if (!Duel_FindTurnMonsterZone(attacker, &turnRow, &col))
    return FALSE;

  return turnRow == gAmazonessCallMultiAttackAnchorRow
      && col == gAmazonessCallMultiAttackAnchorCol;
}

static void MarkDefenderAttacked(struct DuelCard *defender)
{
  u8 turnRow;
  u8 col;

  if (defender == NULL || defender->id == CARD_NONE)
    return;

  if (!Duel_FindTurnMonsterZone(defender, &turnRow, &col))
    return;

  if (turnRow != OpponentMonsterTurnRow())
    return;

  gAmazonessCallMultiAttackedMask |= (1u << col);
}

u8 AmazonessCall_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;

  if (!gAmazonessCallMultiAttackActive || zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return TRUE;

  if (turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return TRUE;

  return turnRow == gAmazonessCallMultiAttackAnchorRow
      && col == gAmazonessCallMultiAttackAnchorCol;
}

void TryUnlockAmazonessCallForNextAttack(struct DuelCard *attacker,
                                         struct DuelCard *defender)
{
  if (!AttackerIsCallMultiAttackAnchor(attacker))
    return;

  if (IsTheDarkDoorActiveOnField())
    return;

  MarkDefenderAttacked(defender);

  if (HasUnattackedOpponentMonster())
    attacker->isLocked = FALSE;
  else
    ClearAmazonessCallMultiAttackState();
}

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidCallMultiAttackTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return Duel_IsAmazonessCard(zone->id);
}

static u8 HasCallMultiAttackTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidCallMultiAttackTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

static void LockOtherActiveMonsters(u8 anchorTurnRow, u8 anchorTurnCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id == CARD_NONE)
      continue;

    if (ACTIVE_DUELIST_MONSTER_ROW == anchorTurnRow && col == anchorTurnCol) {
      zone->isLocked = FALSE;
      continue;
    }

    zone->isLocked = TRUE;
  }
}

static void MarkCallMultiAttackAt(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u8 turnRow;
  u8 turnCol;

  if (!IsValidCallMultiAttackTarget(fixedRow, fixedCol))
    return;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &turnCol))
    return;

  ClearAmazonessCallMultiAttackState();
  gAmazonessCallMultiAttackActive = TRUE;
  gAmazonessCallMultiAttackAnchorRow = turnRow;
  gAmazonessCallMultiAttackAnchorCol = turnCol;
  gAmazonessCallMultiAttackedMask = 0;
  LockOtherActiveMonsters(turnRow, turnCol);
}

static void ResolveCallMultiAttackTarget(u8 fixedRow, u8 fixedCol)
{
  MarkCallMultiAttackAt(fixedRow, fixedCol);
}

static void CancelCallMultiAttackTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickCallMultiAttackTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidCallMultiAttackTarget(fixedRow, col))
      continue;

    zone = gFixedZones[fixedRow][col];
    atk = gCardData_NEW[zone->id].atk;
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outRow = fixedRow;
  *outCol = bestCol;
  return TRUE;
}

u8 CanActivateAmazonessCallGy(u8 fixedDuelist, u8 gyIndex)
{
  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  if (EffectOpt_IsUsed(AMAZONESS_CALL))
    return FALSE;

  if (gyIndex >= GraveyardExpand_GetCount(fixedDuelist))
    return FALSE;

  if (GraveyardExpand_GetCardAt(fixedDuelist, gyIndex) != AMAZONESS_CALL)
    return FALSE;

  return HasCallMultiAttackTarget();
}

void ActivateAmazonessCallGy(u8 fixedDuelist, u8 gyIndex)
{
  if (!CanActivateAmazonessCallGy(fixedDuelist, gyIndex))
    return;

  Duel_ShowEffectText(AMAZONESS_CALL);
  if (IsDuelOver() == TRUE)
    return;

  EffectOpt_MarkUsed(AMAZONESS_CALL);
  Duel_BanishGraveyardAtFixed(fixedDuelist, gyIndex);

  Duel_SetupPickZone(IsValidCallMultiAttackTarget, ResolveCallMultiAttackTarget,
                     CancelCallMultiAttackTargeting, AiPickCallMultiAttackTarget);

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    Duel_RunPickZoneInputLoop();
  else
    Duel_ResolvePickZoneForAi();

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

APPEND_TEXT void EffectAMAZONESS_CALL(void)
{
  if (!CanActivateAmazonessCall()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(AMAZONESS_CALL, AMAZONESS_CALL_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void AMAZONESS_CALL_SelfCheck(void)
{
  if (!Duel_IsAmazonessCard(AMAZONESS_QUEEN))
    while (1)
      ;
  if (Duel_IsAmazonessCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (IsAmazonessCallSearchTarget(AMAZONESS_CALL))
    while (1)
      ;
  if (!IsAmazonessCallSearchTarget(AMAZONESS_QUEEN))
    while (1)
      ;
}
#endif
