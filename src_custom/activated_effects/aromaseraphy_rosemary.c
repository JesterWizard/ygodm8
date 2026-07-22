#include "global.h"
#include "aromaseraphy_rosemary.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

#define ROSEMARY_STAT_BONUS 500

static u8 ControllerHasFaceUpRosemaryWithLpAdvantage(u8 controller)
{
  u8 opp = controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 row;
  u8 col;

  if (gDuelLifePoints[controller] <= gDuelLifePoints[opp])
    return FALSE;

  row = Duel_FixedMonsterRowForDuelist(controller);
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AROMASERAPHY_ROSEMARY)
      return TRUE;
  }
  return FALSE;
}

void ApplyAromaseraphyRosemaryStatBoostToCardInfo(const struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return;
  if (!Duel_CardHasMonsterType(zone->id, TYPE_PLANT))
    return;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return;
  if (!ControllerHasFaceUpRosemaryWithLpAdvantage(controller))
    return;

  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + ROSEMARY_STAT_BONUS);
  gCardInfo.def = Duel_ClampStat((u32)gCardInfo.def + ROSEMARY_STAT_BONUS);
}

static u8 IsFaceUpOppCardTarget(struct DuelCard *zone)
{
  u8 typeGroup;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  if (typeGroup == TYPE_GROUP_MONSTER) {
    if (IsCardFaceUp(zone))
      return TRUE;

    return zone->isDefending == FALSE;
  }

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  return IsFaceUpOppCardTarget(gFixedZones[fixedRow][fixedCol]);
}

static u8 FieldHasTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col))
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

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(fixedRow), FALSE) == DUEL_ACTION_DUEL_OVER)
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
  s8 bestCol = -1;
  u16 bestAtk = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!IsValidTarget(row, col))
        continue;

      zone = gFixedZones[row][col];
      if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }

      atk = Duel_GetZoneFinalAtk(zone);
      if (bestCol < 0 || atk > bestAtk) {
        bestCol = (s8)col;
        bestAtk = atk;
        *outRow = row;
      }
    }
  }

  if (bestCol < 0)
    return FALSE;

  *outCol = (u8)bestCol;
  return TRUE;
}

unsigned char CanActivateAROMASERAPHY_ROSEMARY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMASERAPHY_ROSEMARY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMASERAPHY_ROSEMARY)
    return FALSE;

  /* Plant +500 via ApplyAromaseraphyRosemaryStatBoostToCardInfo.
   * OPT destroy 1 face-up opp (ignition stand-in).
   * LP-gain negate via aroma_lp_gain.c (unk4 |= 0x80). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateAROMASERAPHY_ROSEMARYEffect(void)
{
  Duel_ShowEffectTextTyped(AROMASERAPHY_ROSEMARY, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
