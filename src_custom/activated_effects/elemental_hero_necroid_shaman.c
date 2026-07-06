#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "elemental_hero_necroid_shaman.h"
#include "expanded_graveyard.h"
#include "god_card.h"

extern u16 gNewButtons;
extern u16 gFilteredInput;
extern u16 gPressedButtons;

void UpdateDuelGfxExceptField(void);
void UpdateFilteredInput_NoRepeat(void);
void DeckMenuSort(void);
unsigned IsPlayerDeckNonempty(void);
void RunPlayerDeckTask(u8 task);
void sub_801EF30(u8 task);
void sub_801F4A0(u8 task);
void sub_801F5F0(void);
void sub_801F5FC(void);
void sub_0801F62C(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 FindShamanFixedZone(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    u8 fixedRow;
    u8 fixedCol;

    if (zone->id != ELEMENTAL_HERO_NECROID_SHAMAN)
      continue;

    if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
      continue;

    *outRow = fixedRow;
    *outCol = fixedCol;
    return TRUE;
  }

  return FALSE;
}

static u8 ZoneIsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 FindFirstDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!ZoneIsValidDestroyTarget(OPPONENT_MONSTER_ROW, col))
      continue;

    *outRow = OPPONENT_MONSTER_ROW;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u16 GetMonsterPrintedAtk(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[cardId].atk;
}

static u8 PickAiDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!ZoneIsValidDestroyTarget(OPPONENT_MONSTER_ROW, col))
      continue;

    zone = gFixedZones[OPPONENT_MONSTER_ROW][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outRow = OPPONENT_MONSTER_ROW;
  *outCol = bestCol;
  return TRUE;
}

static u8 OpponentGyMonsterIsValid(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 LoadOpponentGraveyardMonsterMenu(u8 *sourceIndexOut)
{
  u8 gyCount = GraveyardExpand_GetCount(DUEL_OPPONENT);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(DUEL_OPPONENT, i);

    if (!OpponentGyMonsterIsValid(cardId))
      continue;

    sourceIndexOut[menuCount] = i;
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

static u16 OpponentGyMonsterPickerProcessInput(void)
{
  u8 i;
  u16 mask;
  u16 ret = 0;

  UpdateFilteredInput_NoRepeat();

  mask = 1;
  for (i = 0; i < NUM_BUTTONS; i++) {
    if (mask & gNewButtons)
      ret = mask & gNewButtons;
    mask <<= 1;
  }

  mask = DPAD_RIGHT;
  for (i = 0; i < 4; i++) {
    if (mask & gFilteredInput)
      ret = mask & gFilteredInput;
    mask <<= 1;
  }

  if ((gFilteredInput & DPAD_UP) && (gPressedButtons & R_BUTTON))
    ret = DPAD_UP | R_BUTTON;
  if ((gFilteredInput & DPAD_DOWN) && (gPressedButtons & R_BUTTON))
    ret = DPAD_DOWN | R_BUTTON;

  return ret;
}

static u8 FindGyIndexForSortedMenuPick(const u16 *sortedCards, s8 menuIndex)
{
  u16 cardId;
  u8 gyCount;
  u8 sameBefore = 0;
  u8 i;

  if (menuIndex < 0)
    return 0xFF;

  cardId = sortedCards[(u8)menuIndex];
  for (i = 0; i < (u8)menuIndex; i++) {
    if (sortedCards[i] == cardId)
      sameBefore++;
  }

  gyCount = GraveyardExpand_GetCount(DUEL_OPPONENT);
  for (i = 0; i < gyCount; i++) {
    u16 gyCard = GraveyardExpand_GetCardAt(DUEL_OPPONENT, i);

    if (!OpponentGyMonsterIsValid(gyCard))
      continue;
    if (gyCard != cardId)
      continue;
    if (sameBefore == 0)
      return i;
    sameBefore--;
  }

  return 0xFF;
}

static s8 PickOpponentGyMonsterMenuIndex(u16 *sortedCardsOut)
{
  u8 keepProcessing = TRUE;
  s8 selectedIndex = -1;

  if (IsPlayerDeckNonempty() != 1)
    return -1;

  DeckMenu_BeginDuelTrunkView();
  DeckMenuSort();
  sub_801EF30(0);
  sub_801EF30(2);
  sub_801F4A0(1);
  sub_801F5F0();
  sub_801F4A0(3);

  while (keepProcessing) {
    switch (OpponentGyMonsterPickerProcessInput()) {
    case DPAD_UP:
      RunPlayerDeckTask(3);
      sub_801EF30(3);
      sub_801F5FC();
      sub_801F4A0(4);
      break;
    case DPAD_UP | R_BUTTON:
      RunPlayerDeckTask(5);
      sub_801EF30(3);
      sub_801F5FC();
      sub_801F4A0(4);
      break;
    case DPAD_DOWN:
      RunPlayerDeckTask(2);
      sub_801EF30(3);
      sub_801F5FC();
      sub_801F4A0(4);
      break;
    case DPAD_DOWN | R_BUTTON:
      RunPlayerDeckTask(4);
      sub_801EF30(3);
      sub_801F5FC();
      sub_801F4A0(4);
      break;
    case L_BUTTON:
      RunPlayerDeckTask(6);
      sub_801EF30(4);
      sub_801F5FC();
      sub_801F4A0(4);
      break;
    case A_BUTTON:
      selectedIndex = (s8)gDeckMenu.currentPos;
      if (sortedCardsOut != NULL) {
        u8 i;

        for (i = 0; i < gDeckMenu.cardCount; i++)
          sortedCardsOut[i] = gDeckMenu.cards[i];
      }
      keepProcessing = FALSE;
      PlayMusic(SFX_SELECT);
      break;
    case B_BUTTON:
      keepProcessing = FALSE;
      PlayMusic(SFX_CANCEL);
      break;
    case 0:
    default:
      sub_801EF30(5);
      sub_0801F62C();
      sub_801F4A0(5);
      break;
    }

    if (IsPlayerDeckNonempty() != 1)
      keepProcessing = FALSE;
  }

  DeckMenu_EndDuelTrunkView();
  return selectedIndex;
}

static u8 PickOpponentGyMonsterIndexForAi(const u8 *sourceIndices, u8 menuCount)
{
  u8 bestMenuIdx = 0;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < menuCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(DUEL_OPPONENT, sourceIndices[i]);
    u16 atk = GetMonsterPrintedAtk(cardId);

    if (i == 0 || atk >= bestAtk) {
      bestMenuIdx = i;
      bestAtk = atk;
    }
  }

  return sourceIndices[bestMenuIdx];
}

static enum DuelActionResult SpecialSummonOpponentGraveyardMonsterAtIndex(u8 gyIndex)
{
  struct DuelSummonOpts opts;
  u16 cardId;

  if (FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return DUEL_ACTION_NO_ZONE;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard;
    if (!OpponentGyMonsterIsValid(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, CARD_NONE, opts);
  }

  cardId = GraveyardExpand_GetCardAt(DUEL_OPPONENT, gyIndex);
  if (!OpponentGyMonsterIsValid(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(DUEL_OPPONENT, gyIndex);
  GraveyardExpand_SyncLegacyTop(DUEL_OPPONENT);
  return Duel_SpecialSummonMonsterId(INACTIVE_DUELIST, cardId, opts);
}

static void TryReviveOpponentGraveyardMonster(u8 allowPlayerPicker)
{
  u8 sourceIndices[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 gyIndex = 0xFF;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    SpecialSummonOpponentGraveyardMonsterAtIndex(0);
    return;
  }

  menuCount = LoadOpponentGraveyardMonsterMenu(sourceIndices);
  if (menuCount == 0)
    return;

  if (menuCount == 1) {
    SpecialSummonOpponentGraveyardMonsterAtIndex(sourceIndices[0]);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER && allowPlayerPicker) {
    s8 menuIndex;
    u16 sortedMenuCards[EXPANDED_GRAVEYARD_CAPACITY];

    for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
      sortedMenuCards[i] = CARD_NONE;

    DECKMENU_SAVE();

    menuIndex = PickOpponentGyMonsterMenuIndex(sortedMenuCards);

    DECKMENU_RESTORE();

    if (menuIndex < 0)
      return;

    gyIndex = FindGyIndexForSortedMenuPick(sortedMenuCards, menuIndex);
    if (gyIndex == 0xFF)
      return;
  } else {
    gyIndex = PickOpponentGyMonsterIndexForAi(sourceIndices, menuCount);
  }

  SpecialSummonOpponentGraveyardMonsterAtIndex(gyIndex);
}

static void CancelDestroyTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static void ResolveDestroyTarget(u8 targetRow, u8 targetCol)
{
  struct DuelCard *target = gFixedZones[targetRow][targetCol];

  if (!ZoneIsValidDestroyTarget(targetRow, targetCol))
    return;

  if (Duel_DestroyZone(target, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  TryReviveOpponentGraveyardMonster(TRUE);
}

static void BeginNecroidShamanTargeting(u8 originRow, u8 originCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstDestroyTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;

  Duel_SetupPickZone(ZoneIsValidDestroyTarget, ResolveDestroyTarget, CancelDestroyTargeting,
                     PickAiDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static void ResolveNecroidShamanEffectForAi(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!PickAiDestroyTarget(&targetRow, &targetCol))
    return;

  ResolveDestroyTarget(targetRow, targetCol);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void ElementalHeroNecroidShaman_OnFusionSummoned(void)
{
  u8 shamanRow;
  u8 shamanCol;
  u8 targetRow;
  u8 targetCol;

  Duel_ShowEffectText(ELEMENTAL_HERO_NECROID_SHAMAN);

  if (IsDuelOver() == TRUE)
    return;

  if (!FindShamanFixedZone(&shamanRow, &shamanCol))
    return;

  if (!FindFirstDestroyTarget(&targetRow, &targetCol))
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    BeginNecroidShamanTargeting(shamanRow, shamanCol);
  else
    ResolveNecroidShamanEffectForAi();
}
