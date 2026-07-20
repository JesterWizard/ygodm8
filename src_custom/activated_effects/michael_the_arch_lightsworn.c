#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define MICHAEL_LP_COST 1000

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanPayMichaelCost(void)
{
  return gDuelLifePoints[FixedDuelistForActive()] >= MICHAEL_LP_COST;
}

static u8 IsAnyFieldCardZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow > PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE;
}

static u8 FieldHasAnyCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsAnyFieldCardZone(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 TurnDuelistOwningFixedRow(u8 fixedRow)
{
  u8 fixedOwner;

  if (fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW)
    fixedOwner = DUEL_PLAYER;
  else
    fixedOwner = DUEL_OPPONENT;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedOwner])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsAnyFieldCardZone(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)MICHAEL_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_BanishZone(zone, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsAnyFieldCardZone(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (row = PLAYER_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsAnyFieldCardZone(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateMICHAEL_THE_ARCH_LIGHTSWORN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MICHAEL_THE_ARCH_LIGHTSWORN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MICHAEL_THE_ARCH_LIGHTSWORN)
    return FALSE;

  /* ponytail: destroy→shuffle Lightsworn + End Phase mill 3 need destroy/EP
   * hooks. Ceiling: pay 1000 LP → banish 1 field card. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanPayMichaelCost() && FieldHasAnyCard();
}

void ActivateMICHAEL_THE_ARCH_LIGHTSWORNEffect(void)
{
  Duel_ShowEffectTextTyped(MICHAEL_THE_ARCH_LIGHTSWORN, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsAnyFieldCardZone, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
