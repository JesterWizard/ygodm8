#include "global.h"
#include "common-chax.h"
#include "dynamic_equip.h"
#include "mystical_space_typhoon.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);
void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);
void ResetCardEffectTextData(void);
void SetCardEffectTextType(u8);
void ActivateCardEffectText(void);

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 IsSameFixedZone(u8 rowA, u8 colA, u8 rowB, u8 colB)
{
  return rowA == rowB && colA == colB;
}

static u8 IsValidMysticalSpaceTyphoonTargetZone(u8 fixedRow, u8 fixedCol, u8 originFixedRow,
                                                u8 originFixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_BACKROW && fixedRow != PLAYER_BACKROW)
    return FALSE;

  if (IsSameFixedZone(fixedRow, fixedCol, originFixedRow, originFixedCol))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  return IsSpellOrTrapCard(zone->id);
}

static u8 FindFirstMysticalSpaceTyphoonTarget(u8 originFixedRow, u8 originFixedCol, u8 *outRow,
                                              u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidMysticalSpaceTyphoonTargetZone(row, col, originFixedRow, originFixedCol))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 GetTurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

u8 IsMysticalSpaceTyphoonCard(u16 cardId)
{
  return cardId == MYSTICAL_SPACE_TYPHOON;
}

u8 FieldHasMysticalSpaceTyphoonTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 row;
  u8 col;

  return FindFirstMysticalSpaceTyphoonTarget(originFixedRow, originFixedCol, &row, &col);
}

void BeginMysticalSpaceTyphoonTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstMysticalSpaceTyphoonTarget(originFixedRow, originFixedCol, &targetRow, &targetCol))
    return;

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(1);
    gCardEffectTextData.cardId = MYSTICAL_SPACE_TYPHOON;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.state = DUEL_CURSOR_MST_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
}

void TrySelectMysticalSpaceTyphoonTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidMysticalSpaceTyphoonTargetZone(targetRow, targetCol, originRow, originCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.id = MYSTICAL_SPACE_TYPHOON;
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

void CancelMysticalSpaceTyphoonTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

APPEND_TEXT void EffectMysticalSpaceTyphoon(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  if (!IsValidMysticalSpaceTyphoonTargetZone(gSpellEffectData.row1, gSpellEffectData.col1,
                                             gSpellEffectData.row2, gSpellEffectData.col2)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  gTrapEffectData.originRow = gSpellEffectData.row2;
  gTrapEffectData.originCol = gSpellEffectData.col2;
  gTrapEffectData.originCardId = spellZone->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    ClearZoneAndSendMonToGraveyard(target, GetTurnDuelistForFixedRow(gSpellEffectData.row1));
    ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);
    NotifyDynamicEquipFieldChanged();
  } else {
    ActivateTrapEffect(0);
  }

  gTrapEffectData.originRow = 0;
  gTrapEffectData.originCol = 0;
}
