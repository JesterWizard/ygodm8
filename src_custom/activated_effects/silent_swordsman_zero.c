#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

unsigned char CanActivateSILENT_SWORDSMAN_ZERO(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SILENT_SWORDSMAN_ZERO)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SILENT_SWORDSMAN_ZERO)
    return FALSE;

  /* ponytail: Standby Level + Sarcophagus negate need phase/chain hooks.
   * Ceiling: OPT +1 Level mark (unkTwo) + +1 tempStage ATK stand-in. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return TRUE;
}

void ActivateSILENT_SWORDSMAN_ZEROEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(SILENT_SWORDSMAN_ZERO, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (self->unkTwo < 255)
    self->unkTwo = (u8)(self->unkTwo + 1);

  if (self->tempStage < 127)
    self->tempStage = (s8)(self->tempStage + 1);

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
