#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

extern u8 gWhiteStoneSentToGyThisTurn;
extern u8 gWhiteStoneSentToGyPrevTurn;

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sBlueEyesName[] APPEND_RODATA = "Blue-Eyes";

static const u8 sBlueEyesGyPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForActiveTurn(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsBlueEyesMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sBlueEyesName);
}

static u8 GraveyardContainsWhiteStone(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == THE_WHITE_STONE_OF_ANCIENTS;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == THE_WHITE_STONE_OF_ANCIENTS)
      return TRUE;
  }

  return FALSE;
}

static u8 GyHasBlueEyesBesides(u8 fixedDuelist, u8 skipIndex)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (i == skipIndex)
      continue;
    if (IsBlueEyesMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u16 FindBlueEyesInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u8 i;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsBlueEyesMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanSpecialSummonBlueEyesFromDeck(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  return FindBlueEyesInDeck(turnDuelist) != CARD_NONE;
}

static void MarkWhiteStoneSentToGy(u8 controller)
{
  if (controller == DUEL_PLAYER)
    gWhiteStoneSentToGyThisTurn |= 1;
  else if (controller == DUEL_OPPONENT)
    gWhiteStoneSentToGyThisTurn |= 2;
}

static void OnWhiteStoneLeaveField(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != THE_WHITE_STONE_OF_ANCIENTS)
    return;

  MarkWhiteStoneSentToGy(ev->controller);
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

static u8 LoadBlueEyesGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsBlueEyesMonster(cardId))
      continue;

    gyIndexMap[menuCount] = i;
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

static s8 PlayerPickBlueEyesGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadBlueEyesGyMenu(fixedDuelist, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1) {
    chosenGyIndex = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return chosenGyIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sBlueEyesGyPickLabels,
                                         ARRAY_COUNT(sBlueEyesGyPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static s8 FindBestBlueEyesGyIndexForAi(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 bestIndex = 0xFF;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u16 atk;

    if (!IsBlueEyesMonster(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestIndex == 0xFF || atk > bestAtk) {
      bestAtk = atk;
      bestIndex = i;
    }
  }

  return (s8)bestIndex;
}

static u8 AddBlueEyesFromGyToHand(u8 fixedDuelist, s8 gyIndex)
{
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0 || gyIndex < 0 || !GraveyardExpand_IsEnabled())
    return FALSE;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsBlueEyesMonster(cardId))
    return FALSE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  InitHandSlotFromCard(
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
  return TRUE;
}

void TheWhiteStoneOfAncients_AgeSentFlags(void)
{
  gWhiteStoneSentToGyPrevTurn = gWhiteStoneSentToGyThisTurn;
  gWhiteStoneSentToGyThisTurn = 0;
}

void TheWhiteStoneOfAncients_EnsureInit(void)
{
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnWhiteStoneLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnWhiteStoneLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnWhiteStoneLeaveField);
}

u8 ShouldActivateTheWhiteStoneOfAncientsTurnEffect(void)
{
  u8 fixedDuelist;
  u8 bit;

  TheWhiteStoneOfAncients_EnsureInit();

  if (gActiveEffect.cardId != THE_WHITE_STONE_OF_ANCIENTS)
    return FALSE;

  if (gActiveEffect.turnRow != 6)
    return FALSE;

  fixedDuelist = FixedDuelistForActiveTurn();
  bit = (fixedDuelist == DUEL_PLAYER) ? 1 : 2;

  /* Engine runs turn effects at next turn start ≈ End Phase of prior turn. */
  if ((gWhiteStoneSentToGyPrevTurn & bit) == 0)
    return FALSE;

  if (!GraveyardContainsWhiteStone(fixedDuelist))
    return FALSE;

  return CanSpecialSummonBlueEyesFromDeck(ACTIVE_DUELIST);
}

void ActivateTheWhiteStoneOfAncientsTurnEffect(void)
{
  u8 fixedDuelist = FixedDuelistForActiveTurn();
  u8 bit = (fixedDuelist == DUEL_PLAYER) ? 1 : 2;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (!ShouldActivateTheWhiteStoneOfAncientsTurnEffect())
    return;

  gWhiteStoneSentToGyPrevTurn &= (u8)~bit;

  cardId = FindBlueEyesInDeck(ACTIVE_DUELIST);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(THE_WHITE_STONE_OF_ANCIENTS, 9);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts);
}

u8 CanActivateTheWhiteStoneOfAncientsGy(u8 fixedDuelist, u8 gyIndex)
{
  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  if (EffectOpt_IsUsed(THE_WHITE_STONE_OF_ANCIENTS))
    return FALSE;

  if (gyIndex >= GraveyardExpand_GetCount(fixedDuelist))
    return FALSE;

  if (GraveyardExpand_GetCardAt(fixedDuelist, gyIndex) != THE_WHITE_STONE_OF_ANCIENTS)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return GyHasBlueEyesBesides(fixedDuelist, gyIndex);
}

void ActivateTheWhiteStoneOfAncientsGy(u8 fixedDuelist, u8 gyIndex)
{
  s8 blueEyesIndex;

  if (!CanActivateTheWhiteStoneOfAncientsGy(fixedDuelist, gyIndex))
    return;

  Duel_ShowEffectTextTyped(THE_WHITE_STONE_OF_ANCIENTS, 9);
  if (IsDuelOver() == TRUE)
    return;

  EffectOpt_MarkUsed(THE_WHITE_STONE_OF_ANCIENTS);
  Duel_BanishGraveyardAtFixed(fixedDuelist, gyIndex);

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    blueEyesIndex = PlayerPickBlueEyesGyIndex(fixedDuelist);
  else
    blueEyesIndex = FindBestBlueEyesGyIndexForAi(fixedDuelist);

  if (blueEyesIndex < 0)
    return;

  if (!AddBlueEyesFromGyToHand(fixedDuelist, blueEyesIndex))
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
