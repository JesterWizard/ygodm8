#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_rampart_blaster.h"
#include "monster_effect_usage.h"

unsigned char CanActivateElementalHeroRampartBlaster(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return Duel_GetZoneFinalAtk(zone) / 2 > 0;
}

void ActivateElementalHeroRampartBlasterEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 damage = Duel_GetZoneFinalAtk(zone) / 2;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_RAMPART_BLASTER, 2);

  if (IsDuelOver() || damage == 0)
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)damage, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}
