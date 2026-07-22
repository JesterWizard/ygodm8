#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "summon_tribute.h"
#include "mobius_the_frost_monarch.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void SetCursorToCardDest(void);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 IsSameFixedZone(u8 rowA, u8 colA, u8 rowB, u8 colB)
{
  return rowA == rowB && colA == colB;
}

static u8 IsSpellOrTrapType(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 IsValidMobiusTargetZone(u8 fixedRow, u8 fixedCol, u8 originFixedRow,
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

  return IsSpellOrTrapType(zone->id);
}

static u8 FindFirstMobiusTarget(u8 originFixedRow, u8 originFixedCol, u8 *outRow,
                                u8 *outCol)
{
  u8 col;

  /* Scan opponent backrow first, then player backrow */
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidMobiusTargetZone(OPPONENT_BACKROW, col, originFixedRow, originFixedCol))
      continue;

    *outRow = OPPONENT_BACKROW;
    *outCol = col;
    return TRUE;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidMobiusTargetZone(PLAYER_BACKROW, col, originFixedRow, originFixedCol))
      continue;

    *outRow = PLAYER_BACKROW;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 GetDuelistForFixedZone(u8 fixedRow)
{
  u8 turn = WhoseTurn();

  if (fixedRow == PLAYER_BACKROW || fixedRow == PLAYER_MONSTER_ROW)
    return turn == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
  if (fixedRow == OPPONENT_BACKROW || fixedRow == OPPONENT_MONSTER_ROW)
    return turn == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  return 0xFF;
}

static void DestroyMobiusTarget(u8 targetRow, u8 targetCol)
{
  struct DuelCard *target = gFixedZones[targetRow][targetCol];
  u8 duelist = GetDuelistForFixedZone(targetRow);

  if (duelist == 0xFF)
    return;

  Duel_DestroyZone(target, duelist, FALSE);
  NotifyDynamicEquipFieldChanged();
}

static void MarkMobiusEffectUsed(u8 originFixedRow, u8 originFixedCol)
{
  gFixedZones[originFixedRow][originFixedCol]->unk4 = 1;
}

static void ShowMobiusActivationText(void)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  Duel_ShowEffectTextTyped(MOBIUS_THE_FROST_MONARCH, 8);
  gHideEffectText = hideEffectText;
}

u8 FieldHasMobiusTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 row;
  u8 col;

  return FindFirstMobiusTarget(originFixedRow, originFixedCol, &row, &col);
}

unsigned char ShouldActivateMobiusTheFrostMonarch(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != MOBIUS_THE_FROST_MONARCH)
    return FALSE;

  if (GetPendingTributeSummonCardId() != MOBIUS_THE_FROST_MONARCH)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return FieldHasMobiusTarget(gActiveEffect.turnRow, gActiveEffect.col);
}

static void BeginMobiusTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstMobiusTarget(originFixedRow, originFixedCol, &targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_MOBIUS_THE_FROST_MONARCH_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originFixedRow, targetRow);
}

static void FinishMobiusEffect(u8 originFixedRow, u8 originFixedCol)
{
  MarkMobiusEffectUsed(originFixedRow, originFixedCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originFixedRow;
  gDuelCursor.currentX = originFixedCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

/* up-to-2 targeting uses zone->unk4 as phase flag.
   0 = not started, 1+ = at least one target destroyed (re-entered targeting).
   Upgrade path: bitfield on zone if unk4 is needed for other purposes. */
static u8 MobiusShouldContinueToSecondTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (gFixedZones[originFixedRow][originFixedCol]->unk4 >= 2)
    return FALSE;

  return FindFirstMobiusTarget(originFixedRow, originFixedCol, &targetRow, &targetCol);
}

static void ResolveMobiusEffectForAi(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  /* First target */
  if (FindFirstMobiusTarget(originFixedRow, originFixedCol, &targetRow, &targetCol))
    DestroyMobiusTarget(targetRow, targetCol);

  /* Second target — skip unk4 check since AI fires once */
  if (FindFirstMobiusTarget(originFixedRow, originFixedCol, &targetRow, &targetCol))
    DestroyMobiusTarget(targetRow, targetCol);

  MarkMobiusEffectUsed(originFixedRow, originFixedCol);
}

void TrySelectMobiusTheFrostMonarchTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidMobiusTargetZone(targetRow, targetCol, originRow, originCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  DestroyMobiusTarget(targetRow, targetCol);

  /* Mark first destroy and check if we should offer a second target */
  gFixedZones[originRow][originCol]->unk4 = 1;

  if (MobiusShouldContinueToSecondTarget(originRow, originCol)) {
    BeginMobiusTargeting(originRow, originCol);
    return;
  }

  gFixedZones[originRow][originCol]->unk4 = 2;
  FinishMobiusEffect(originRow, originCol);
}

void CancelMobiusTheFrostMonarchTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  MarkMobiusEffectUsed(gDuelCursor.destY, gDuelCursor.destX);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

void ActivateMobiusTheFrostMonarch(void)
{
  u8 originRow = gActiveEffect.turnRow;
  u8 originCol = gActiveEffect.col;

  ShowMobiusActivationText();

  if (WhoseTurn() == DUEL_PLAYER && originRow == ACTIVE_DUELIST_MONSTER_ROW) {
    BeginMobiusTargeting(originRow, originCol);
    return;
  }

  ResolveMobiusEffectForAi(originRow, originCol);
}
