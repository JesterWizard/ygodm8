#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(void);
void TryActivatingPermanentEffects(void);

static u8 IsOppSpellTrapZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 typeGroup;

  if (fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 OppHasSpellTrap(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppSpellTrapZone(OPPONENT_BACKROW, col))
      return TRUE;
  }

  return FALSE;
}

static u8 GraveyardDuelistForBackrow(u8 fixedRow)
{
  if (fixedRow == OPPONENT_BACKROW)
    return INACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOppSpellTrapZone(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, GraveyardDuelistForBackrow(fixedRow), TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = OPPONENT_BACKROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppSpellTrapZone(OPPONENT_BACKROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateAMAZONESS_SAGE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_SAGE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AMAZONESS_SAGE)
    return FALSE;

  /* ponytail: end-of-Damage-Step-after-attack trigger needs battle hook.
   * Ceiling: once via usage if opp Spell/Trap on field; upgrade: damage-step gate. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OppHasSpellTrap();
}

void ActivateAMAZONESS_SAGEEffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_SAGE, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOppSpellTrapZone, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
