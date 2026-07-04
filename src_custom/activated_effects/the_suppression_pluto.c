#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "the_suppression_pluto.h"

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
void TryActivatingPermanentEffects(void);

extern u16 gNewButtons;
extern u16 gRepeatedOrNewButtons;
extern u16 gPressedButtons;
extern u8 gHideEffectText;

static u8 IsFaceUpPlutoSummon(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != THE_SUPPRESSION_PLUTO)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  /* Attack-position summons stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 OpponentBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_BACKROW : PLAYER_BACKROW;
}

static u8 ControllerBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

static u8 ControllerHasEmptyBackrowSlot(void)
{
  return FirstEmptyZoneInRow(gFixedZones[ControllerBackrowFixedRow()]) >= 0;
}

static u8 IsValidTakeControlTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OpponentBackrowFixedRow())
    return FALSE;

  if (!ControllerHasEmptyBackrowSlot())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsSpellOrTrapCard(zone->id);
}

static u8 CountOpponentSpellTraps(void)
{
  u8 row = OpponentBackrowFixedRow();
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTakeControlTarget(row, col))
      count++;
  }

  return count;
}

static u8 CanTakeControlOfOpponentSpellTrap(void)
{
  return ControllerHasEmptyBackrowSlot() && CountOpponentSpellTraps() > 0;
}

static u8 FindFirstTakeControlTarget(u8 *outRow, u8 *outCol)
{
  u8 row = OpponentBackrowFixedRow();
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidTakeControlTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void TakeControlOfSpellTrap(u8 srcRow, u8 srcCol)
{
  struct DuelCard *src = gFixedZones[srcRow][srcCol];
  u8 dstRow = ControllerBackrowFixedRow();
  s8 dstCol = FirstEmptyZoneInRow(gFixedZones[dstRow]);
  struct DuelCard *dst;

  if (src == NULL || src->id == CARD_NONE || dstCol < 0)
    return;

  if (!IsValidTakeControlTarget(srcRow, srcCol))
    return;

  dst = gFixedZones[dstRow][dstCol];
  CopyCard(dst, src);
  dst->willChangeSides = FALSE;
  ClearZone(src);
  NotifyDynamicEquipFieldChanged();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Returns: 1 = picked, 0 = cancelled (B), 0xFF = no targets. */
static u8 PickTakeControlTarget(u8 originRow, u8 *outRow, u8 *outCol)
{
  struct DuelCursor savedCursor = gDuelCursor;
  u8 scrollY;
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstTakeControlTarget(&targetRow, &targetCol))
    return 0xFF;

  InitButtonMaps();
  gDuelCursor.currentY = targetRow;
  gDuelCursor.destY = originRow;
  gDuelCursor.currentX = targetCol;
  gDuelCursor.destX = savedCursor.destX;
  DisplayCardInfoBar();
  sub_8041E70(originRow, targetRow);

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
      if (IsValidTakeControlTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
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

void TryTheSuppressionPlutoOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;
  u8 targetRow;
  u8 targetCol;
  u8 pick;

  if (!IsFaceUpPlutoSummon(zone))
    return;

  if (!CanTakeControlOfOpponentSpellTrap())
    return;

  /* ponytail: on-summon text after field draw so Pluto is visible. */
  UpdateDuelGfxExceptField();

  Duel_ShowEffectTextTyped(THE_SUPPRESSION_PLUTO, 2);
  if (IsDuelOver() == TRUE)
    return;

  if (!FindFirstTakeControlTarget(&targetRow, &targetCol))
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
      return;

    pick = PickTakeControlTarget(fixedRow, &targetRow, &targetCol);
    if (pick == 0 || pick == 0xFF)
      return;
  }

  TakeControlOfSpellTrap(targetRow, targetCol);
  UpdateDuelGfxExceptField();
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TheSuppressionPluto_SelfCheck(void)
{
  if (!IsSpellOrTrapCard(POLYMERIZATION))
    while (1)
      ;

  if (IsSpellOrTrapCard(CYBER_DRAGON))
    while (1)
      ;
}
#endif
