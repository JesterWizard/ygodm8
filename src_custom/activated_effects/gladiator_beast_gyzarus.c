#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "gladiator_beast_battled.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

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

static u8 IsMonsterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 FieldHasMonsterTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsMonsterTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void DestroySecondMonster(u8 skipRow, u8 skipCol)
{
  u8 row;
  u8 col;
  s8 bestRow = -1;
  s8 bestCol = -1;
  u16 bestAtk = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (row == skipRow && col == skipCol)
        continue;

      if (!IsMonsterTarget(row, col))
        continue;

      zone = gFixedZones[row][col];
      atk = Duel_GetZoneFinalAtk(zone);
      if (bestCol < 0 || atk > bestAtk) {
        bestRow = (s8)row;
        bestCol = (s8)col;
        bestAtk = atk;
      }
    }
  }

  if (bestCol < 0)
    return;

  Duel_DestroyZone(gFixedZones[(u8)bestRow][(u8)bestCol],
                   TurnDuelistOwningFixedRow((u8)bestRow), TRUE);
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsMonsterTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(fixedRow), TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() != TRUE)
    DestroySecondMonster(fixedRow, fixedCol);

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

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  s8 bestRow = -1;
  s8 bestCol = -1;
  u16 bestAtk = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!IsMonsterTarget(row, col))
        continue;

      zone = gFixedZones[row][col];
      atk = Duel_GetZoneFinalAtk(zone);
      if (bestCol < 0 || atk > bestAtk) {
        bestRow = (s8)row;
        bestCol = (s8)col;
        bestAtk = atk;
      }
    }
  }

  if (bestCol < 0)
    return FALSE;

  *outRow = (u8)bestRow;
  *outCol = (u8)bestCol;
  return TRUE;
}

unsigned char CanActivateGLADIATOR_BEAST_GYZARUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GLADIATOR_BEAST_GYZARUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GLADIATOR_BEAST_GYZARUS)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FieldHasMonsterTarget())
    return TRUE;

  return GladiatorBeast_CanActivateDeckTagOutTwo(GLADIATOR_BEAST_GYZARUS, zone);
}

void ActivateGLADIATOR_BEAST_GYZARUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_GYZARUS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (FieldHasMonsterTarget()) {
    gDuelCursor.destY = gMonEffect.row;
    gDuelCursor.destX = gMonEffect.zone;
    Duel_SetupPickZone(IsMonsterTarget, ResolveDestroyTarget, CancelTargeting,
                       AiPickDestroyTarget);

    if (WhoseTurn() == DUEL_PLAYER)
      Duel_EnterPickZoneTargeting();
    else
      Duel_ResolvePickZoneForAi();
    return;
  }

  GladiatorBeast_ActivateDeckTagOutTwo(self, GLADIATOR_BEAST_GYZARUS);
}
