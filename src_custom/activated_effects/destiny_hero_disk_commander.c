#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateDESTINY_HERO_DISK_COMMANDER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_DISK_COMMANDER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DISK_COMMANDER)
    return FALSE;

  /* ponytail: SS-from-GY trigger + once per duel. Ceiling: OPT draw 2 stand-in
   * when on field; upgrade: GY SS dispatch + EFFECT_USAGE_ONCE. */
  return CanUseMonsterEffect(zone);
}

void ActivateDESTINY_HERO_DISK_COMMANDEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(DESTINY_HERO_DISK_COMMANDER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, 2, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
