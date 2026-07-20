#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(void);
void TryActivatingPermanentEffects(void);

#define ANCIENT_GEAR_CANNON_DAMAGE 500

unsigned char CanActivateANCIENT_GEAR_CANNON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_CANNON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_CANNON)
    return FALSE;

  return CanUseMonsterEffect(zone);
}

void ActivateANCIENT_GEAR_CANNONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_CANNON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(self, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)ANCIENT_GEAR_CANNON_DAMAGE, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: Battle Phase Trap lock not applied; upgrade: trap-activation gate. */

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
