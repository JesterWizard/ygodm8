#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

#define GRAVEKEEPERS_CURSE_DAMAGE 500

unsigned char CanActivateGRAVEKEEPERS_CURSE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRAVEKEEPERS_CURSE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRAVEKEEPERS_CURSE)
    return FALSE;

  /* printed is If Summoned trigger. Ceiling: allow once via usage
   * when manually activated / summon-dispatch calls Activate. */
  return CanUseMonsterEffect(zone);
}

void ActivateGRAVEKEEPERS_CURSEEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_CURSE, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  Duel_ChangeLp(INACTIVE_DUELIST, -GRAVEKEEPERS_CURSE_DAMAGE, TRUE);
  MarkMonsterEffectUsed(zone);
}
