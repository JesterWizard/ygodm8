#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

extern unsigned char IsSkillDrainActiveOnField(void);
extern unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId);
extern void UpdateDuelGfxExceptField(void);

#define ARCHLORD_KRISTYA_REQUIRED_FAIRY_GY_COUNT 4

static const u8 sArchlordKristyaPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsFairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].type == TYPE_FAIRY;
}

static u8 CountFairyMonstersInGraveyard(u8 fixedDuelist)
{
  u8 count = 0;
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsFairyMonster(cardId) ? 1 : 0;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsFairyMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 GraveyardHasTargetableFairy(u8 fixedDuelist)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsFairyMonster(cardId);
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsFairyMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
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

static void PlaceCardOnDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 LoadFairyGraveyardPickMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsFairyMonster(cardId))
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

static s8 FindBestFairyGyIndexForAi(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 bestIndex = 0xFF;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u16 atk;

    if (!IsFairyMonster(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestIndex == 0xFF || atk > bestAtk) {
      bestAtk = atk;
      bestIndex = i;
    }
  }

  return (s8)bestIndex;
}

static s8 GyIndexForSortedMenuPick(u8 fixedDuelist, u8 menuPos, u8 menuCount)
{
  u16 cardId;
  u8 occurrence = 0;
  u8 seen = 0;
  u8 i;
  u8 gyCount;

  if (menuPos >= menuCount)
    return -1;

  cardId = gDeckMenu.cards[menuPos];
  if (cardId == CARD_NONE)
    return -1;

  for (i = 0; i <= menuPos; i++) {
    if (gDeckMenu.cards[i] == cardId)
      occurrence++;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 gyCard = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsFairyMonster(gyCard))
      continue;

    if (gyCard == cardId) {
      seen++;
      if (seen == occurrence)
        return (s8)i;
    }
  }

  return -1;
}

static s8 PlayerPickFairyGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 j;
  s8 chosenGyIndex;

  menuCount = LoadFairyGraveyardPickMenu(fixedDuelist, gyIndexMap);
  if (menuCount == 0)
    return -1;

  if (menuCount == 1)
    return (s8)gyIndexMap[0];

  DECKMENU_SAVE();

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sArchlordKristyaPickLabels, ARRAY_COUNT(sArchlordKristyaPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = GyIndexForSortedMenuPick(fixedDuelist, gDeckMenu.currentPos, menuCount);

  DECKMENU_RESTORE();

  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static u8 AddGraveyardFairyToHand(u8 turnDuelist, u8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = GetGraveCardAndClearGrave(fixedDuelist);
    if (!IsFairyMonster(cardId))
      return FALSE;
  } else {
    cardId = GraveyardExpand_RemoveAtTurn(turnDuelist, gyIndex);
    if (!IsFairyMonster(cardId))
      return FALSE;

    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    GraveyardExpand_RefreshDisplay();
  }

  InitHandSlotFromCard(gTurnHands[turnDuelist][handZone], cardId);
  return TRUE;
}

static void ResolveArchlordKristyaGyToHand(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 gyIndex;

  if (!GraveyardHasTargetableFairy(fixedDuelist))
    return;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  Duel_ShowEffectTextTyped(ARCHLORD_KRISTYA, 1);

  if (IsDuelOver() == TRUE)
    return;

  if (IsSkillDrainActiveOnField() && TryActivateSkillDrainAndNegateCardId(ARCHLORD_KRISTYA))
    return;

  if (WhoseTurn() == DUEL_PLAYER && GraveyardExpand_IsEnabled())
    gyIndex = PlayerPickFairyGyIndex(fixedDuelist);
  else
    gyIndex = FindBestFairyGyIndexForAi(fixedDuelist);

  if (gyIndex < 0)
    return;

  AddGraveyardFairyToHand(turnDuelist, (u8)gyIndex);
  UpdateDuelGfxExceptField();
}

void ClearArchlordKristyaState(void)
{
  gArchlordKristyaEffectSummon = FALSE;
}

u8 ArchlordKristya_IsSpecialSummonLocked(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id == ARCHLORD_KRISTYA && zone->isFaceUp)
        return TRUE;
    }
  }

  return FALSE;
}

u8 ArchlordKristya_ShouldBlockFieldPlacement(u16 cardId, u8 tributesPaid)
{
  if (!ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (tributesPaid > 0)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  /* ponytail: engine treats level 5+ with no tribute as special-like (Cyber Dragon, etc.). */
  return gCardInfo.level > 4;
}

u8 ArchlordKristya_TrySendFaceUpFieldToDeckTop(struct DuelCard *zone, u8 turnDuelist)
{
  u8 fixedRow;
  u8 col;
  u8 fixedDuelist;
  u16 cardId;

  if (zone == NULL || zone->id != ARCHLORD_KRISTYA || !zone->isFaceUp)
    return FALSE;

  if (Duel_ZoneIsHandSlot(zone))
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  cardId = zone->id;
  fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  PlaceCardOnDeckTop(fixedDuelist, cardId);
  return TRUE;
}

u8 CanSpecialSummonArchlordKristyaFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (handZone >= MAX_ZONES_IN_ROW)
    return FALSE;

  if (handRow[handZone]->id != ARCHLORD_KRISTYA)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  if (CountFairyMonstersInGraveyard(fixedDuelist) != ARCHLORD_KRISTYA_REQUIRED_FAIRY_GY_COUNT)
    return FALSE;

  return GraveyardHasTargetableFairy(fixedDuelist);
}

static void EnsureArchlordKristyaSummonedFaceUp(void)
{
  u8 col;
  struct DuelCard *zone;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    if (zone->id != ARCHLORD_KRISTYA)
      continue;

    zone->isFaceUp = TRUE;
    zone->isDefending = FALSE;
    zone->isLocked = FALSE;
    UnlockCard(zone);
    Duel_NotifyMonsterZoneChanged(zone);
    return;
  }
}

u8 TrySpecialSummonArchlordKristyaFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  if (!CanSpecialSummonArchlordKristyaFromHand(handZone))
    return FALSE;

  gArchlordKristyaEffectSummon = TRUE;
  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK) {
    gArchlordKristyaEffectSummon = FALSE;
    return FALSE;
  }

  gArchlordKristyaEffectSummon = FALSE;
  EnsureArchlordKristyaSummonedFaceUp();
  ResolveArchlordKristyaGyToHand(ACTIVE_DUELIST);
  return TRUE;
}

#if defined(ARCHLORD_KRISTYA_SELF_CHECK)
void ArchlordKristya_SelfCheck(void)
{
  if (!IsFairyMonster(TINY_ANGEL))
    while (1)
      ;
  if (CountFairyMonstersInGraveyard(DUEL_PLAYER) > ARCHLORD_KRISTYA_REQUIRED_FAIRY_GY_COUNT)
    while (1)
      ;
}
#endif
