#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsValidFiendTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != gMonEffect.row)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (fixedCol == gMonEffect.zone)
    return FALSE;

  return Duel_CardHasMonsterType(zone->id, TYPE_FIEND);
}

static u8 FieldHasFiendTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidFiendTarget(gMonEffect.row, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveFiendTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidFiendTarget(fixedRow, fixedCol) || target == NULL || self == NULL)
    return;

  MarkMonsterEffectUsed(self);

  if (Duel_BanishZone(self, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  /* second Standby Phase GY return needs turn/Standby hook; unk4=2 extra attack
   * via TryUnlockUnk4MarkedExtraAttack. */
  target->unk4 = 2;
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickFiendTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  s8 bestCol = -1;
  u16 bestAtk = 0;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[*outRow][col];
    u16 atk;

    if (!IsValidFiendTarget(*outRow, col))
      continue;

    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol < 0 || atk > bestAtk) {
      bestCol = (s8)col;
      bestAtk = atk;
    }
  }

  if (bestCol < 0)
    return FALSE;

  *outCol = (u8)bestCol;
  return TRUE;
}

unsigned char CanActivateEVIL_HERO_INFERNAL_GAINER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != EVIL_HERO_INFERNAL_GAINER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != EVIL_HERO_INFERNAL_GAINER)
    return FALSE;

  /* Main Phase 1 gate needs phase hook. Extra attack via TryUnlockUnk4MarkedExtraAttack
   * when unk4=2; second Standby GY return needs Standby hook. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasFiendTarget();
}

void ActivateEVIL_HERO_INFERNAL_GAINEREffect(void)
{
  Duel_ShowEffectTextTyped(EVIL_HERO_INFERNAL_GAINER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidFiendTarget, ResolveFiendTarget, CancelTargeting,
                     AiPickFiendTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
