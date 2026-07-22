#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "silent_swordsman.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

void TryApplySilentSwordsmanZeroStandby(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id != SILENT_SWORDSMAN_ZERO || !zone->isFaceUp)
      continue;

    Duel_ShowEffectTextTyped(SILENT_SWORDSMAN_ZERO, 9);

    if (zone->unkTwo < 255)
      zone->unkTwo = (u8)(zone->unkTwo + 1);

    if (zone->tempStage < 127)
      zone->tempStage = (s8)(zone->tempStage + 1);

    RefreshFieldMonsterStatOverlays();
  }
}

unsigned char CanActivateSILENT_SWORDSMAN_ZERO(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SILENT_SWORDSMAN_ZERO)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SILENT_SWORDSMAN_ZERO)
    return FALSE;

  /* Standby Level/ATK via TryApplySilentSwordsmanZeroStandby; OPT +1 Level/+1
   * tempStage unchanged. ponytail: Sarcophagus negate needs chain hook. */
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
