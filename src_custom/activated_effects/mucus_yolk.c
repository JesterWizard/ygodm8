#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

unsigned char CanActivateMUCUS_YOLK(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MUCUS_YOLK)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MUCUS_YOLK)
    return FALSE;

  /* ponytail: direct attack + Standby +1000 after battle damage need battle/EP hooks.
   * Ceiling: OPT +2 tempStage (~1000 ATK stand-in for printed Standby gain). */
  return CanUseMonsterEffect(zone);
}

void ActivateMUCUS_YOLKEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(MUCUS_YOLK, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (self->tempStage < 126)
    self->tempStage += 2;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
