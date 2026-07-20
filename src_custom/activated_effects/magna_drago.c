#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

unsigned char CanActivateMAGNA_DRAGO(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MAGNA_DRAGO)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MAGNA_DRAGO)
    return FALSE;

  /* ponytail: battle-damage trigger needs battle hook.
   * Ceiling: OPT +1 stage (~500; printed +200) stand-in. */
  return CanUseMonsterEffect(zone);
}

void ActivateMAGNA_DRAGOEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(MAGNA_DRAGO, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  IncrementPermStage(zone);
  MarkMonsterEffectUsed(zone);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
