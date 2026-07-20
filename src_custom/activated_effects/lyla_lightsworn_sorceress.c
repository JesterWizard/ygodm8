#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOppFaceUpSpellTrapZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 typeGroup;

  if (fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 FieldHasOppFaceUpSpellTrap(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppFaceUpSpellTrapZone(OPPONENT_BACKROW, col))
      return TRUE;
  }

  return FALSE;
}

static u8 SelfIsFaceUpAttack(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsCardFaceUp(zone) && zone->isDefending == FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOppFaceUpSpellTrapZone(fixedRow, fixedCol) || target == NULL || self == NULL)
    return;

  if (!SelfIsFaceUpAttack(self))
    return;

  self->isDefending = TRUE;
  self->isFaceUp = TRUE;

  if (Duel_DestroyZone(target, INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
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
  u8 col;

  *outRow = OPPONENT_BACKROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppFaceUpSpellTrapZone(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateLYLA_LIGHTSWORN_SORCERESS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LYLA_LIGHTSWORN_SORCERESS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LYLA_LIGHTSWORN_SORCERESS)
    return FALSE;

  /* ponytail: position-lock + End Phase mill 3 need battle/EP hooks. Ceiling:
   * OPT from face-up ATK: change to face-up DEF and destroy 1 opp Spell/Trap. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return SelfIsFaceUpAttack(zone) && FieldHasOppFaceUpSpellTrap();
}

void ActivateLYLA_LIGHTSWORN_SORCERESSEffect(void)
{
  Duel_ShowEffectTextTyped(LYLA_LIGHTSWORN_SORCERESS, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOppFaceUpSpellTrapZone, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
