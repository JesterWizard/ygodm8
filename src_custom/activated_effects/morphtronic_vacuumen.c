#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define VACUUMEN_BURN 500

unsigned char CanActivateMORPHTRONIC_VACUUMEN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_VACUUMEN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_VACUUMEN)
    return FALSE;

  /* ponytail: send Equip → burn + DEF equip-take-control need equip hooks.
   * Ceiling: ATK Position OPT burn 500. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return zone->isDefending == FALSE;
}

void ActivateMORPHTRONIC_VACUUMENEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(MORPHTRONIC_VACUUMEN, 2);

  if (self == NULL || IsDuelOver() == TRUE || self->isDefending != FALSE)
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -VACUUMEN_BURN, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
