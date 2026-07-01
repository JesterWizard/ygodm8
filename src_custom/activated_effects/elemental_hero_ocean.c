#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_ocean.h"
#include "expanded_graveyard.h"
#include "gfx_reg_buffers.h"
#include "monster_effect_usage.h"

extern u16 gNewButtons;
extern u16 gFilteredInput;
extern u16 gPressedButtons;

void ClearGraphicsBuffers(void);
void UpdateAllDuelGfx(void);
void UpdateFilteredInput_NoRepeat(void);
void DeckMenuSort(void);
unsigned IsPlayerDeckNonempty(void);
void RunPlayerDeckTask(u8 task);
void sub_801EF30(u8 task);
void sub_801F4A0(u8 task);
void sub_801F5F0(void);
void sub_801F5FC(void);
void sub_0801F62C(void);

static void Ocean_RestoreDuelGfxAfterPick(void)
{
  UpdateAllDuelGfx();
}

#define OCEAN_TARGET_FIELD 0
#define OCEAN_TARGET_GRAVE 1

static const char sHeroArchetypeName[] APPEND_RODATA = "HERO";

struct OceanTargetRef {
  u8 kind;
  u8 index;
};

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHeroArchetypeName);
}

static u8 Ocean_IsActivatingZone(u8 fixedRow, u8 fixedCol)
{
  if (gMonEffect.id != ELEMENTAL_HERO_OCEAN)
    return FALSE;

  return gMonEffect.row == fixedRow && gMonEffect.zone == fixedCol;
}

static u8 Ocean_ActivatorOnField(void)
{
  return gTurnZones[gMonEffect.row][gMonEffect.zone]->id == ELEMENTAL_HERO_OCEAN;
}

static u8 Ocean_FieldTargetAllowed(u8 fixedRow, u8 fixedCol)
{
  if (!IsHeroMonster(gFixedZones[fixedRow][fixedCol]->id))
    return FALSE;

  if (Ocean_IsActivatingZone(fixedRow, fixedCol))
    return FALSE;

  return TRUE;
}

static u8 Ocean_GraveyardTargetAllowed(u8 turnDuelist, u8 graveyardIndex, u16 cardId)
{
  if (!IsHeroMonster(cardId))
    return FALSE;

  // ponytail: skip stale GY Ocean while the activator is still on field
  if (cardId == ELEMENTAL_HERO_OCEAN && Ocean_ActivatorOnField())
    return FALSE;

  return TRUE;
}

static u8 ActiveMonsterRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;

  return DUEL_PLAYER;
}

static u16 CardIdForOceanTarget(u8 turnDuelist, const struct OceanTargetRef *target)
{
  if (target->kind == OCEAN_TARGET_FIELD)
    return gFixedZones[ActiveMonsterRow()][target->index]->id;

  if (!GraveyardExpand_IsEnabled())
    return gTurnDuelistBattleState[turnDuelist]->graveyard;

  return GraveyardExpand_GetCardAt(TurnDuelistToFixed(turnDuelist), target->index);
}

static u8 CountOceanTargets(u8 turnDuelist)
{
  struct OceanTargetRef refs[MAX_ZONES_IN_ROW + EXPANDED_GRAVEYARD_CAPACITY];
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u8 monsterRow = ActiveMonsterRow();
  u8 count = 0;
  u8 col;
  u8 i;
  u8 gyCount;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (Ocean_FieldTargetAllowed(monsterRow, col)) {
      refs[count].kind = OCEAN_TARGET_FIELD;
      refs[count].index = col;
      count++;
    }
  }

  if (!GraveyardExpand_IsEnabled()) {
    if (Ocean_GraveyardTargetAllowed(turnDuelist, 0,
                                     gTurnDuelistBattleState[turnDuelist]->graveyard)) {
      refs[count].kind = OCEAN_TARGET_GRAVE;
      refs[count].index = 0;
      count++;
    }
    return count;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (Ocean_GraveyardTargetAllowed(turnDuelist, i, cardId)) {
      refs[count].kind = OCEAN_TARGET_GRAVE;
      refs[count].index = i;
      count++;
    }
  }

  return count;
}

static u8 LoadOceanTargets(u8 turnDuelist, struct OceanTargetRef *refs, u8 maxRefs)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u8 monsterRow = ActiveMonsterRow();
  u8 count = 0;
  u8 col;
  u8 i;
  u8 gyCount;

  for (col = 0; col < MAX_ZONES_IN_ROW && count < maxRefs; col++) {
    if (!Ocean_FieldTargetAllowed(monsterRow, col))
      continue;

    refs[count].kind = OCEAN_TARGET_FIELD;
    refs[count].index = col;
    count++;
  }

  if (!GraveyardExpand_IsEnabled()) {
    if (count < maxRefs
        && Ocean_GraveyardTargetAllowed(turnDuelist, 0,
                                        gTurnDuelistBattleState[turnDuelist]->graveyard)) {
      refs[count].kind = OCEAN_TARGET_GRAVE;
      refs[count].index = 0;
      count++;
    }
    return count;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount && count < maxRefs; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!Ocean_GraveyardTargetAllowed(turnDuelist, i, cardId))
      continue;

    refs[count].kind = OCEAN_TARGET_GRAVE;
    refs[count].index = i;
    count++;
  }

  return count;
}

static u8 LoadOceanTargetMenu(const struct OceanTargetRef *refs, u8 refCount)
{
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < refCount; i++)
    gDeckMenu.cards[i] = CardIdForOceanTarget(ACTIVE_DUELIST, &refs[i]);

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = refCount;
  return refCount;
}

static u16 OceanTargetPickerProcessInput(void)
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

static s8 PickOceanTargetMenuIndex(void)
{
  u8 keepProcessing = TRUE;
  s8 selectedIndex = -1;

  if (IsPlayerDeckNonempty() != 1)
    return -1;

  ClearGraphicsBuffers();
  LoadOam();
  LoadPalettes();
  DisableDisplay();
  DeckMenuSort();
  sub_801EF30(0);
  sub_801EF30(2);
  sub_801F4A0(1);
  sub_801F5F0();
  sub_801F4A0(3);

  while (keepProcessing) {
    switch (OceanTargetPickerProcessInput()) {
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

  Ocean_RestoreDuelGfxAfterPick();
  return selectedIndex;
}

static u8 InitHandSlotFromCardId(u8 turnDuelist, u16 cardId)
{
  s8 handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  struct DuelCard *handSlot;

  if (handZone < 0)
    return FALSE;

  handSlot = gTurnHands[turnDuelist][handZone];
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
  return TRUE;
}

static u8 ReturnGraveyardHeroToHand(u8 turnDuelist, u8 graveyardIndex)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = GetGraveCardAndClearGrave(fixedDuelist);
    if (!IsHeroMonster(cardId))
      return FALSE;
  } else {
    cardId = GraveyardExpand_RemoveAtTurn(turnDuelist, graveyardIndex);
    if (!IsHeroMonster(cardId))
      return FALSE;

    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    GraveyardExpand_RefreshDisplay();
  }

  return InitHandSlotFromCardId(turnDuelist, cardId);
}

static u8 ResolveOceanTarget(const struct OceanTargetRef *target)
{
  if (target->kind == OCEAN_TARGET_FIELD) {
    struct DuelCard *zone = gFixedZones[ActiveMonsterRow()][target->index];

    if (!Ocean_FieldTargetAllowed(ActiveMonsterRow(), target->index))
      return FALSE;

    return Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK;
  }

  return ReturnGraveyardHeroToHand(ACTIVE_DUELIST, target->index);
}

static u8 IsValidFieldTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != ActiveMonsterRow())
    return FALSE;

  return Ocean_FieldTargetAllowed(fixedRow, fixedCol);
}

static void ResolveFieldTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!IsValidFieldTarget(fixedRow, fixedCol))
    return;

  zone = gFixedZones[fixedRow][fixedCol];
  if (Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK)
    Ocean_RestoreDuelGfxAfterPick();
}

static void CancelFieldTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickFieldTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 monsterRow = ActiveMonsterRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!Ocean_FieldTargetAllowed(monsterRow, col))
      continue;

    *outRow = monsterRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 PickOceanTargetForPlayer(const struct OceanTargetRef *refs, u8 refCount,
                                   struct OceanTargetRef *outTarget)
{
  u8 fieldOnly = TRUE;
  u8 i;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  s8 menuIndex;

  for (i = 0; i < refCount; i++) {
    if (refs[i].kind != OCEAN_TARGET_FIELD) {
      fieldOnly = FALSE;
      break;
    }
  }

  if (fieldOnly && refCount > 1) {
    gDuelCursor.destY = ActiveMonsterRow();
    gDuelCursor.destX = refs[0].index;
    Duel_SetupPickZone(IsValidFieldTarget, ResolveFieldTarget, CancelFieldTargeting,
                       AiPickFieldTarget);
    Duel_EnterPickZoneTargeting();
    return FALSE;
  }

  if (refCount == 1) {
    *outTarget = refs[0];
    return TRUE;
  }

  for (i = 0; i < sizeof(gDeckMenu); i++)
    savedDeckMenu[i] = ((u8 *)&gDeckMenu)[i];

  LoadOceanTargetMenu(refs, refCount);
  menuIndex = PickOceanTargetMenuIndex();

  for (i = 0; i < sizeof(gDeckMenu); i++)
    ((u8 *)&gDeckMenu)[i] = savedDeckMenu[i];

  if (menuIndex < 0)
    return FALSE;

  *outTarget = refs[(u8)menuIndex];
  return TRUE;
}

static u8 PickOceanTargetForAi(const struct OceanTargetRef *refs, u8 refCount,
                               struct OceanTargetRef *outTarget)
{
  u8 i;

  for (i = 0; i < refCount; i++) {
    if (refs[i].kind == OCEAN_TARGET_FIELD) {
      *outTarget = refs[i];
      return TRUE;
    }
  }

  *outTarget = refs[0];
  return TRUE;
}

unsigned char CanActivateElementalHeroOcean(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return CountOceanTargets(ACTIVE_DUELIST) > 0;
}

void ActivateElementalHeroOceanEffect(void)
{
  struct OceanTargetRef refs[MAX_ZONES_IN_ROW + EXPANDED_GRAVEYARD_CAPACITY];
  struct OceanTargetRef chosenTarget;
  u8 refCount;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_OCEAN, 2);

  if (IsDuelOver() == TRUE)
    return;

  refCount = LoadOceanTargets(ACTIVE_DUELIST, refs, ARRAY_COUNT(refs));
  if (refCount == 0)
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    if (!PickOceanTargetForPlayer(refs, refCount, &chosenTarget))
      return;
  } else if (!PickOceanTargetForAi(refs, refCount, &chosenTarget)) {
    return;
  }

  if (!ResolveOceanTarget(&chosenTarget))
    return;

  Ocean_RestoreDuelGfxAfterPick();
}

#if !defined(__GNUC__)
unsigned char CanActivateElementalHeroOcean(void);
void ActivateElementalHeroOceanEffect(void);
#endif
