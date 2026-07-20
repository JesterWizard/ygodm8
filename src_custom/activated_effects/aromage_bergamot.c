#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

unsigned char CanActivateAROMAGE_BERGAMOT(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMAGE_BERGAMOT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMAGE_BERGAMOT)
    return FALSE;

  /* ponytail: LP-higher Plant piercing + LP-gain gate + until opp EP clear need
   * permanent/LP/battle hooks. Ceiling: OPT +2 tempStage (~1000 ATK/DEF). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return TRUE;
}

void ActivateAROMAGE_BERGAMOTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(AROMAGE_BERGAMOT, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (self->tempStage < 126)
    self->tempStage += 2;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
