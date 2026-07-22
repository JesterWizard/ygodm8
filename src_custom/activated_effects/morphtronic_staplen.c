#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "morphtronic_staplen.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOppAtkPositionMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return zone->isDefending == FALSE;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  return IsOppAtkPositionMonster(gFixedZones[fixedRow][fixedCol]);
}

static u8 FieldHasTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(INACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  zone->isDefending = TRUE;
  zone->isFaceUp = TRUE;

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

  *outRow = INACTIVE_DUELIST_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(INACTIVE_DUELIST_MONSTER_ROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

u8 MorphtronicStaplen_PreventsBattleDestroy(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != MORPHTRONIC_STAPLEN)
    return FALSE;

  return zone->isDefending;
}

struct DuelCard *MorphtronicStaplen_GetForcedAttackTarget(u8 defenderDuelist)
{
  u8 fixedRow = Duel_FixedMonsterRowForDuelist(defenderDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == NULL || zone->id != MORPHTRONIC_STAPLEN || !zone->isFaceUp)
      continue;
    if (zone->isDefending)
      continue;

    return zone;
  }

  return NULL;
}

u8 MorphtronicStaplen_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE || zone->id == MORPHTRONIC_STAPLEN)
    return TRUE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return TRUE;

  return MorphtronicStaplen_GetForcedAttackTarget(
      Duel_FixedDuelistForMonsterRow(fixedRow)) == NULL;
}

unsigned char CanActivateMORPHTRONIC_STAPLEN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_STAPLEN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_STAPLEN)
    return FALSE;

  /* DEF battle indestructible via MorphtronicStaplen_PreventsBattleDestroy; ATK
   * redirect via MorphtronicStaplen_GetForcedAttackTarget. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateMORPHTRONIC_STAPLENEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_STAPLEN, 2);

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
