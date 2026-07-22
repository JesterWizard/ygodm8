#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static u8 IsValidTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != gMonEffect.row)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return zone->id != DARK_STRIKE_FIGHTER;
}

static u8 FieldHasTributeTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTributeTarget(gMonEffect.row, col))
      return TRUE;
  }

  return FALSE;
}

static s32 BurnForTributedMonster(u16 cardId)
{
  u8 level;

  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return 0;

  level = gCardData_NEW[cardId].level;
  if (level == 0)
    return 0;

  return (s32)level * 200;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;
  s32 damage;

  if (!IsValidTributeTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  cardId = zone->id;
  damage = BurnForTributedMonster(cardId);

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (damage > 0
      && Duel_ChangeLp(INACTIVE_DUELIST, -damage, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

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
  u8 col;
  u8 bestCol = 0;
  u8 found = FALSE;
  s32 bestDamage = 0;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    s32 damage;

    if (!IsValidTributeTarget(*outRow, col))
      continue;

    damage = BurnForTributedMonster(gFixedZones[*outRow][col]->id);
    if (!found || damage > bestDamage) {
      found = TRUE;
      bestDamage = damage;
      bestCol = col;
    }
  }

  if (!found)
    return FALSE;

  *outCol = bestCol;
  return TRUE;
}

unsigned char CanActivateDARK_STRIKE_FIGHTER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DARK_STRIKE_FIGHTER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DARK_STRIKE_FIGHTER)
    return FALSE;

  /* Ceiling: Main Phase 1 gate not wired; allow once via usage any main phase. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTributeTarget();
}

void ActivateDARK_STRIKE_FIGHTEREffect(void)
{
  Duel_ShowEffectTextTyped(DARK_STRIKE_FIGHTER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTributeTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
