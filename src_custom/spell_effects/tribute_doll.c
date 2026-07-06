#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"
#include "tribute_doll.h"

#define TRIBUTE_DOLL_SUMMON_LEVEL 7

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void MoveCursorLeft(void);
void MoveCursorRight(void);
void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);
void ActivateSpellEffect(void);
void ResetCursorDestToCurrentPos(void);
void SetCursorToCardDest(void);
void TryActivatingPermanentEffects(void);
void UnlockCardsInRow(unsigned char turnRow);
void LockMonsterCardsInRow(unsigned char turnRow);

extern u16 gNewButtons;
extern u16 gRepeatedOrNewButtons;
extern u16 gPressedButtons;

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 ZoneIsTributeableMonster(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 IsTributeDollSummonTarget(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);

  if (gCardInfo.level != TRIBUTE_DOLL_SUMMON_LEVEL)
    return FALSE;

  return gCardInfo.color == COLOR_NORMAL || gCardInfo.color == COLOR_EFFECT;
}

static u8 HandHasTributeDollSummonTarget(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsTributeDollSummonTarget(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 FindFirstTributeTarget(u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!ZoneIsTributeableMonster(gFixedZones[fixedRow][col]))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 FieldHasTributeTarget(void)
{
  u8 col;

  return FindFirstTributeTarget(&col);
}

static u8 IsValidTributeTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  return ZoneIsTributeableMonster(gFixedZones[fixedRow][fixedCol]);
}

static u8 CanSpecialSummonTributeDollTarget(void)
{
  if (!HandHasTributeDollSummonTarget(gTurnHands[ACTIVE_DUELIST]))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

u8 CanActivateTributeDoll(void)
{
  if (!FieldHasTributeTarget())
    return FALSE;

  return CanSpecialSummonTributeDollTarget();
}

static u8 IsTributeDollTargetingConfirm(void)
{
  u8 row = gSpellEffectData.row1;

  return row == PLAYER_MONSTER_ROW || row == OPPONENT_MONSTER_ROW;
}

static s8 PickAiSummonHandZone(struct DuelCard **handRow)
{
  u8 i;
  s8 chosenZone = -1;
  u16 bestAtk = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = handRow[i]->id;

    if (!IsTributeDollSummonTarget(cardId))
      continue;

    SetCardInfo(cardId);
    if (chosenZone < 0 || gCardInfo.atk > bestAtk) {
      chosenZone = i;
      bestAtk = gCardInfo.atk;
    }
  }

  return chosenZone;
}

static void SpecialSummonTributeDollTarget(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 relockHand = FALSE;
  s8 handZone;

  opts.lockMonster = TRUE;

  if (!CanSpecialSummonTributeDollTarget())
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked) {
      UnlockCardsInRow(ACTIVE_DUELIST_HAND);
      relockHand = TRUE;
    }

    handZone = SelectHandCardMatchingPredicatePinnedFieldRow(
        gTurnHands[ACTIVE_DUELIST], IsTributeDollSummonTarget, ActiveMonsterFixedRow());
    if (handZone < 0) {
      if (relockHand)
        LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);
      return;
    }

    if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_DUEL_OVER)
      return;

    if (relockHand)
      LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);
    return;
  }

  handZone = PickAiSummonHandZone(gTurnHands[ACTIVE_DUELIST]);

  if (handZone >= 0)
    Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts);
}

static u8 AiPickTributeTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidTributeTarget(fixedRow, col))
      continue;

    zone = gFixedZones[fixedRow][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk < bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = fixedRow;
      *outCol = col;
    }
  }

  return found;
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

static u8 PlayerPickTributeTarget(u8 *outRow, u8 *outCol)
{
  struct DuelCursor savedCursor = gDuelCursor;
  u8 scrollY;
  u8 monsterRow = ActiveMonsterFixedRow();
  u8 targetCol;

  if (!FindFirstTributeTarget(&targetCol))
    return FALSE;

  InitButtonMaps();
  gDuelCursor.currentY = monsterRow;
  gDuelCursor.destY = monsterRow;
  gDuelCursor.currentX = targetCol;
  gDuelCursor.destX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(savedCursor.currentY, monsterRow);

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
    } else if (gNewButtons & A_BUTTON) {
      if (IsValidTributeTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
        PlayMusic(SFX_SELECT);
        *outRow = gDuelCursor.currentY;
        *outCol = gDuelCursor.currentX;
        gDuelCursor = savedCursor;
        return TRUE;
      }
      PlayMusic(SFX_FORBIDDEN);
    }

    WaitForVBlank();
  }
}

static void ResolveTributeDollCore(struct DuelCard *spellZone, u8 tributeRow, u8 tributeCol)
{
  struct DuelCard *tributeZone = gFixedZones[tributeRow][tributeCol];

  if (!IsValidTributeTarget(tributeRow, tributeCol) || !CanSpecialSummonTributeDollTarget())
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckLevelLimitAreaAAfterFieldChange();

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonTributeDollTarget();
}

void BeginTributeDollTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;
  u8 monsterRow = ActiveMonsterFixedRow();

  if (!FindFirstTributeTarget(&targetCol))
    return;

  Duel_ShowEffectText(TRIBUTE_DOLL);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_TRIBUTE_DOLL_TARGET;
  gDuelCursor.currentY = monsterRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originFixedRow, monsterRow);
}

void TrySelectTributeDollTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidTributeTarget(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.id = TRIBUTE_DOLL;
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

void CancelTributeDollTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

APPEND_TEXT void EffectTRIBUTE_DOLL(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (IsTributeDollTargetingConfirm()) {
    spellZone = gTurnZones[gSpellEffectData.row2][gSpellEffectData.col2];

    if (!IsValidTributeTarget(gSpellEffectData.row1, gSpellEffectData.col1)
        || !CanSpecialSummonTributeDollTarget()) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveTributeDollCore(spellZone, gSpellEffectData.row1, gSpellEffectData.col1);
    return;
  }

  if (!CanActivateTributeDoll()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER) {
    u8 tributeRow;
    u8 tributeCol;

    if (!PlayerPickTributeTarget(&tributeRow, &tributeCol))
      return;

    ResolveTributeDollCore(spellZone, tributeRow, tributeCol);
    return;
  }

  {
    u8 tributeRow = ActiveMonsterFixedRow();
    u8 tributeCol;

    if (!AiPickTributeTarget(&tributeRow, &tributeCol))
      return;

    ResolveTributeDollCore(spellZone, tributeRow, tributeCol);
  }
}
