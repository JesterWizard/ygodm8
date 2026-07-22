#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 FieldHasSpellCounterOnActiveSide(void)
{
  u8 row;
  u8 col;

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE && zone->unk4 >= 1)
        return TRUE;
    }
  }

  return FALSE;
}

static u8 RemoveOneSpellCounterFromActiveField(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 row;
  u8 col;

  if (self != NULL && self->unk4 >= 1) {
    self->unk4--;
    return TRUE;
  }

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE && zone->unk4 >= 1) {
        zone->unk4--;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static u8 IsValidOppTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasOppTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidOppTarget(row, col))
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

  if (!IsValidOppTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (!RemoveOneSpellCounterFromActiveField())
    return;

  if (Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(fixedRow), FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  EffectOpt_MarkUsed(ARCANITE_MAGICIAN);
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
      if (IsValidOppTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateARCANITE_MAGICIAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ARCANITE_MAGICIAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ARCANITE_MAGICIAN)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (EffectOpt_IsUsed(ARCANITE_MAGICIAN))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!FieldHasSpellCounterOnActiveSide())
    return FALSE;

  return FieldHasOppTarget();
}

void ActivateARCANITE_MAGICIANEffect(void)
{
  Duel_ShowEffectTextTyped(ARCANITE_MAGICIAN, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(ARCANITE_MAGICIAN))
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidOppTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
