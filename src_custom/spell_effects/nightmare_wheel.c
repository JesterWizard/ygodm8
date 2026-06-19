#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "imperial_order.h"
#include "nightmare_wheel.h"

#define NIGHTMARE_WHEEL_STANDBY_DAMAGE 500

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);

static u8 NightmareWheelTargetFixedRow(struct DuelCard *spellZone)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedZone(spellZone, &fixedRow, &col))
    return 0xFF;

  if (fixedRow == PLAYER_BACKROW)
    return OPPONENT_MONSTER_ROW;

  if (fixedRow == OPPONENT_BACKROW)
    return PLAYER_MONSTER_ROW;

  return 0xFF;
}

static u8 NightmareWheelHasTarget(struct DuelCard *spellZone)
{
  return spellZone != NULL && spellZone->id == NIGHTMARE_WHEEL && spellZone->isFaceUp == TRUE
      && spellZone->unk4 > 0;
}

static void NightmareWheelSetTarget(struct DuelCard *spellZone, u8 targetCol)
{
  spellZone->unk4 = targetCol + 1;
}

static struct DuelCard *NightmareWheelGetTarget(struct DuelCard *spellZone)
{
  u8 targetRow;
  u8 targetCol;
  struct DuelCard *target;

  if (!NightmareWheelHasTarget(spellZone))
    return NULL;

  targetRow = NightmareWheelTargetFixedRow(spellZone);
  if (targetRow == 0xFF)
    return NULL;

  targetCol = spellZone->unk4 - 1;
  target = gFixedZones[targetRow][targetCol];
  if (target == NULL || target->id == CARD_NONE)
    return NULL;

  if (GetTypeGroup(target->id) != TYPE_GROUP_MONSTER)
    return NULL;

  return target;
}

static u8 IsValidNightmareWheelTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 FindFirstNightmareWheelTarget(u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidNightmareWheelTargetZone(OPPONENT_MONSTER_ROW, col))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 NightmareWheelZoneTargetsMonster(struct DuelCard *spellZone, struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (!NightmareWheelHasTarget(spellZone))
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return FALSE;

  return fixedRow == NightmareWheelTargetFixedRow(spellZone) && fixedCol == spellZone->unk4 - 1;
}

static void DestroyNightmareWheelForLostTarget(struct DuelCard *spellZone)
{
  u8 fixedRow;
  u8 col;
  u8 graveyardDuelist;

  if (spellZone == NULL || spellZone->id != NIGHTMARE_WHEEL)
    return;

  if (!Duel_FindFixedZone(spellZone, &fixedRow, &col))
    return;

  graveyardDuelist = (fixedRow == PLAYER_BACKROW) ? DUEL_PLAYER : DUEL_OPPONENT;
  spellZone->unk4 = 0;
  Duel_DestroyZone(spellZone, graveyardDuelist, TRUE);
}

static u8 NightmareWheelIsNegated(void)
{
  return IsImperialOrderNegatingSpell(NIGHTMARE_WHEEL);
}

u8 IsNightmareWheelCard(u16 cardId)
{
  return cardId == NIGHTMARE_WHEEL;
}

u8 IsActivatedNightmareWheelZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == NIGHTMARE_WHEEL && zone->isFaceUp == TRUE && zone->unk4 > 0;
}

u8 CanActivateNightmareWheel(void)
{
  return FieldHasNightmareWheelTarget(0, 0);
}

u8 FieldHasNightmareWheelTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;
  return FindFirstNightmareWheelTarget(&col);
}

void BeginNightmareWheelTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;

  if (!FindFirstNightmareWheelTarget(&targetCol))
    return;

  Duel_ShowEffectTextTyped(NIGHTMARE_WHEEL, 1);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_NIGHTMARE_WHEEL_TARGET;
  gDuelCursor.currentY = OPPONENT_MONSTER_ROW;
  gDuelCursor.currentX = targetCol;
}

void TrySelectNightmareWheelTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidNightmareWheelTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.id = NIGHTMARE_WHEEL;
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

void CancelNightmareWheelTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

u8 NightmareWheel_CanMonsterDeclareAttack(const struct DuelCard *zone)
{
  u8 row;
  u8 col;
  struct DuelCard *spellZone;

  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  if (NightmareWheelIsNegated())
    return TRUE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      spellZone = gFixedZones[row][col];
      if (!NightmareWheelHasTarget(spellZone))
        continue;
      if (NightmareWheelZoneTargetsMonster(spellZone, (struct DuelCard *)zone))
        return FALSE;
    }
  }

  return TRUE;
}

u8 NightmareWheel_CannotChangeBattlePosition(const struct DuelCard *zone)
{
  u8 row;
  u8 col;
  struct DuelCard *spellZone;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (NightmareWheelIsNegated())
    return FALSE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      spellZone = gFixedZones[row][col];
      if (!NightmareWheelHasTarget(spellZone))
        continue;
      if (NightmareWheelZoneTargetsMonster(spellZone, (struct DuelCard *)zone))
        return TRUE;
    }
  }

  return FALSE;
}

void TryApplyNightmareWheelOnTargetLeave(struct DuelCard *zone)
{
  u8 row;
  u8 col;
  struct DuelCard *spellZone;

  if (gHideEffectText || zone == NULL)
    return;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      spellZone = gFixedZones[row][col];
      if (!NightmareWheelHasTarget(spellZone))
        continue;
      if (NightmareWheelZoneTargetsMonster(spellZone, zone))
        DestroyNightmareWheelForLostTarget(spellZone);
    }
  }
}

void TryApplyNightmareWheelStandbyDamage(void)
{
  u8 i;
  struct DuelCard *spellZone;
  struct DuelCard *target;

  if (IsDuelOver() == TRUE || NightmareWheelIsNegated())
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    spellZone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];
    if (!NightmareWheelHasTarget(spellZone))
      continue;

    target = NightmareWheelGetTarget(spellZone);
    if (target == NULL)
      continue;

    Duel_ShowEffectTextTyped(NIGHTMARE_WHEEL, 9);
    if (IsDuelOver() == TRUE)
      return;

    if (Duel_ChangeLp(INACTIVE_DUELIST, -NIGHTMARE_WHEEL_STANDBY_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

APPEND_TEXT void EffectNightmareWheel(void)
{
  struct DuelCard *spellZone;

  if (!IsValidNightmareWheelTargetZone(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];
  if (spellZone->id != NIGHTMARE_WHEEL)
    return;

  if (!spellZone->isFaceUp)
    Duel_ActivateContinuousZone(spellZone);

  NightmareWheelSetTarget(spellZone, gSpellEffectData.col1);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void NightmareWheel_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = NIGHTMARE_WHEEL;
  zone.isFaceUp = TRUE;
  zone.unk4 = 0;
  if (IsActivatedNightmareWheelZone(&zone))
    __builtin_trap();

  zone.unk4 = 2;
  if (!IsActivatedNightmareWheelZone(&zone))
    __builtin_trap();
}
#endif
