#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dust_tornado.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);
void MoveCursorLeft(void);
void MoveCursorRight(void);
void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gRepeatedOrNewButtons;
extern u16 gPressedButtons;

#define PLAYER_HAND_ROW 4

static struct DuelCard *TrapOriginZone(u8 row, u8 col)
{
  if (row == ACTIVE_DUELIST_HAND)
    return gTurnHands[ACTIVE_DUELIST][col];

  return gFixedZones[row][col];
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 IsSpellOrTrapHandCard(u16 cardId)
{
  return cardId != CARD_NONE && IsSpellOrTrapCard(cardId);
}

static u8 IsValidDustTornadoTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  return IsSpellOrTrapCard(zone->id);
}

static u8 FindFirstDustTornadoTarget(u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidDustTornadoTargetZone(OPPONENT_BACKROW, col))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 HandHasSettableSpellTrap(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsSpellOrTrapHandCard(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static s8 FindFirstSettableHandZone(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsSpellOrTrapHandCard(gTurnHands[ACTIVE_DUELIST][i]->id))
      return (s8)i;
  }

  return -1;
}

static u8 HandZoneHasSettableSpellTrap(u8 handCol)
{
  return IsSpellOrTrapHandCard(gTurnHands[ACTIVE_DUELIST][handCol]->id);
}
static s8 SelectOptionalSpellTrapFromHand(void)
{
  struct DuelCursor savedCursor = gDuelCursor;
  u8 scrollY;
  u8 running;
  s8 firstZone;

  firstZone = FindFirstSettableHandZone();
  if (firstZone < 0)
    return -1;

  InitButtonMaps();
  gDuelCursor.currentY = PLAYER_HAND_ROW;
  gDuelCursor.destY = PLAYER_HAND_ROW;
  gDuelCursor.currentX = (u8)firstZone;
  gDuelCursor.destX = gDuelCursor.currentX;
  DisplayCardInfoBar();
  sub_8041E70(savedCursor.currentY, PLAYER_HAND_ROW);

  WaitForNoButtonsHeld();
  InitButtonMaps();

  running = TRUE;
  while (running) {
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
    } else if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_CANCEL);
      return -1;
    } else if (gNewButtons & A_BUTTON) {
      if (HandZoneHasSettableSpellTrap(gDuelCursor.currentX)) {
        PlayMusic(SFX_SELECT);
        running = FALSE;
      } else {
        PlayMusic(SFX_FORBIDDEN);
      }
    }

    WaitForVBlank();
  }

  return (s8)gDuelCursor.currentX;
}

static void SetHandCardFaceDownOnBackrow(s8 handCol, s8 backrowCol)
{
  struct DuelCard *handZone = gTurnHands[ACTIVE_DUELIST][handCol];
  struct DuelCard *backrowZone = gTurnZones[ACTIVE_DUELIST_BACKROW][backrowCol];

  CopyCard(backrowZone, handZone);
  backrowZone->isFaceUp = FALSE;
  backrowZone->isLocked = FALSE;
  backrowZone->isDefending = FALSE;
  backrowZone->unk4 = 0;
  backrowZone->unkTwo = 0;
  backrowZone->willChangeSides = FALSE;
  ResetPermStage(backrowZone);
  ResetTempStage(backrowZone);
  ClearZone(handZone);
}

static void TryOptionalSetFromHand(void)
{
  s8 handCol;
  s8 backrowCol;

  if (NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]) <= 0)
    return;
  if (!HandHasSettableSpellTrap())
    return;

  handCol = SelectOptionalSpellTrapFromHand();
  if (handCol < 0)
    return;

  backrowCol = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (backrowCol < 0)
    return;

  SetHandCardFaceDownOnBackrow(handCol, backrowCol);
}

static u8 GetTargetGraveyardDuelist(u8 targetFixedRow)
{
  if (targetFixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

u8 IsDustTornadoCard(u16 cardId)
{
  return cardId == DUST_TORNADO;
}

u8 FieldHasDustTornadoTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;
  return FindFirstDustTornadoTarget(&col);
}

void BeginDustTornadoTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;

  if (!FindFirstDustTornadoTarget(&targetCol))
    return;

  Duel_ShowEffectTextTyped(DUST_TORNADO, 3);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_DUST_TORNADO_TARGET;
  gDuelCursor.currentY = OPPONENT_BACKROW;
  gDuelCursor.currentX = targetCol;
}

void TrySelectDustTornadoTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidDustTornadoTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.id = DUST_TORNADO;
  gSpellEffectData.row1 = targetRow;
  gSpellEffectData.col1 = targetCol;
  gSpellEffectData.row2 = originRow;
  gSpellEffectData.col2 = originCol;
  ActivateSpellEffect();
  gDuelCursor.state = 0;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  TryActivatingPermanentEffects();
}

void CancelDustTornadoTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

APPEND_TEXT void EffectDustTornado(void)
{
  struct DuelCard *target;
  struct DuelCard *trapZone;

  if (!IsValidDustTornadoTargetZone(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  trapZone = TrapOriginZone(gSpellEffectData.row2, gSpellEffectData.col2);

  if (trapZone->id != DUST_TORNADO)
    return;

  if (Duel_DestroyZone(target, GetTargetGraveyardDuelist(gSpellEffectData.row1), FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (Duel_DestroyZone(trapZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();

  if (IsDuelOver() == TRUE)
    return;

  TryOptionalSetFromHand();
  UpdateDuelGfxExceptField();
}
