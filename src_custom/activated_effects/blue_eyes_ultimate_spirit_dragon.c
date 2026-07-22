#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

unsigned char CanActivateBLUE_EYES_ULTIMATE_SPIRIT_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BLUE_EYES_ULTIMATE_SPIRIT_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BLUE_EYES_ULTIMATE_SPIRIT_DRAGON)
    return FALSE;

  /* OPT +2 tempStage (~+1000) as interrupt stand-in (EffectOpt).
   * Quick field negate + destroy-SS FALSE; GY banish-lock FALSE. */
  if (EffectOpt_IsUsed(BLUE_EYES_ULTIMATE_SPIRIT_DRAGON))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return TRUE;
}

void ActivateBLUE_EYES_ULTIMATE_SPIRIT_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(BLUE_EYES_ULTIMATE_SPIRIT_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(BLUE_EYES_ULTIMATE_SPIRIT_DRAGON))
    return;

  if (self->tempStage <= 125)
    self->tempStage = (s8)(self->tempStage + 2);

  EffectOpt_MarkUsed(BLUE_EYES_ULTIMATE_SPIRIT_DRAGON);
  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
