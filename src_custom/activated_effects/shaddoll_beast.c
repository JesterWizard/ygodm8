#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateSHADDOLL_BEAST(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SHADDOLL_BEAST)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SHADDOLL_BEAST)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return CanUseMonsterEffect(zone);
}

void ActivateSHADDOLL_BEASTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(SHADDOLL_BEAST, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
