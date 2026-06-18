#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "ring_of_destruction.h"
#include "royal_decree.h"
#include "spell_effects.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void sub_802ACC0(void);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);

extern u8 gRingOfDestructionPending;

static u16 GetTargetOriginalAtk(struct DuelCard *zone)
{
  SetCardInfo(zone->id);
  return gCardInfo.atk;
}

static u8 IsValidRingOfDestructionTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u16 atk;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  atk = GetTargetOriginalAtk(zone);
  if (atk > gDuelLifePoints[DUEL_OPPONENT])
    return FALSE;

  return TRUE;
}

static u8 FindHighestAtkRingOfDestructionTarget(u8 *outCol)
{
  u8 col;
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 atk;

    if (!IsValidRingOfDestructionTargetZone(OPPONENT_MONSTER_ROW, col))
      continue;

    atk = GetTargetOriginalAtk(gFixedZones[OPPONENT_MONSTER_ROW][col]);
    if (!found || atk > bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outCol = col;
    }
  }

  return found;
}

static u8 FindTurnZoneForCard(struct DuelCard *zone, u8 *turnRow, u8 *col)
{
  u8 row;

  if (zone == NULL)
    return FALSE;

  for (row = 0; row <= 4; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gTurnZones[row][*col] == zone) {
        *turnRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static void PresentRingTrapForEffectText(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 turnRow;
  u8 turnCol;
  u8 prevY;

  if (gHideEffectText || zone == NULL)
    return;

  if (!Duel_FindFixedZone(zone, &fixedRow, &col))
    return;

  prevY = gDuelCursor.currentY;
  gDuelCursor.currentY = fixedRow;
  gDuelCursor.currentX = col;
  sub_8041E70(prevY, fixedRow);

  if (gRuntimeConfig.turn_off_visual_scanner)
    return;

  if (!FindTurnZoneForCard(zone, &turnRow, &turnCol))
    return;

  gActiveEffect.turnRow = turnRow;
  gActiveEffect.col = turnCol;
  gActiveEffect.cardId = RING_OF_DESTRUCTION;
  sub_8034FEC(0x177);
  sub_802ACC0();
}

static void ResolveRingOfDestruction(struct DuelCard *trapZone, struct DuelCard *target)
{
  u16 atk;

  if (trapZone == NULL || target == NULL)
    return;

  if (!trapZone->isFaceUp) {
    PresentRingTrapForEffectText(trapZone);
    Duel_ShowEffectTextTyped(RING_OF_DESTRUCTION, 3);

    if (IsDuelOver() == TRUE)
      return;
  }

  trapZone->isFaceUp = TRUE;
  atk = GetTargetOriginalAtk(target);

  if (Duel_DestroyZone(target, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)atk, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)atk, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
}

static void TryActivateRingForOpponentMonsterRow(void)
{
  u8 targetCol;
  struct DuelCard *trapZone;
  struct DuelCard *target;

  if (WhoseTurn() != DUEL_OPPONENT)
    return;

  if (IsRoyalDecreeActiveOnField())
    return;

  trapZone = Duel_FindBackrowCardOnField(RING_OF_DESTRUCTION, FALSE);
  if (trapZone == NULL || trapZone->isFaceUp != FALSE)
    return;

  if (!FindHighestAtkRingOfDestructionTarget(&targetCol))
    return;

  target = gFixedZones[OPPONENT_MONSTER_ROW][targetCol];
  ResolveRingOfDestruction(trapZone, target);
  UpdateDuelGfxExceptField();
}

u8 IsRingOfDestructionCard(u16 cardId)
{
  return cardId == RING_OF_DESTRUCTION;
}

u8 CanActivateRingOfDestruction(void)
{
  if (WhoseTurn() != DUEL_OPPONENT)
    return FALSE;

  return FieldHasRingOfDestructionTarget(0, 0);
}

u8 FieldHasRingOfDestructionTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;
  return FindHighestAtkRingOfDestructionTarget(&col);
}

void TryRingOfDestructionOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 turnRow;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  if (WhoseTurn() != DUEL_OPPONENT)
    return;

  if (Duel_FindFixedMonsterZone(zone, &fixedRow, &col)) {
    if (fixedRow == OPPONENT_MONSTER_ROW)
      gRingOfDestructionPending = TRUE;
    return;
  }

  if (Duel_FindTurnMonsterZone(zone, &turnRow, &col) && turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    gRingOfDestructionPending = TRUE;
}

void RingOfDestruction_CheckAfterFieldChange(void)
{
  if (gHideEffectText)
    return;

  if (!gRingOfDestructionPending)
    return;

  gRingOfDestructionPending = FALSE;

  if (IsDuelOver() == TRUE)
    return;

  TryActivateRingForOpponentMonsterRow();
}

void BeginRingOfDestructionTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;

  if (!FindHighestAtkRingOfDestructionTarget(&targetCol))
    return;

  Duel_ShowEffectTextTyped(RING_OF_DESTRUCTION, 3);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_RING_OF_DESTRUCTION_TARGET;
  gDuelCursor.currentY = OPPONENT_MONSTER_ROW;
  gDuelCursor.currentX = targetCol;
}

void TrySelectRingOfDestructionTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidRingOfDestructionTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.id = RING_OF_DESTRUCTION;
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

void CancelRingOfDestructionTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

APPEND_TEXT void EffectRingOfDestruction(void)
{
  struct DuelCard *target;
  struct DuelCard *trapZone;

  if (!IsValidRingOfDestructionTargetZone(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  trapZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  if (trapZone->id != RING_OF_DESTRUCTION)
    return;

  ResolveRingOfDestruction(trapZone, target);
}
