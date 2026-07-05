#include "global.h"
#include "duel_helpers.h"

void ApplyMahaVailoEquipBonus(struct DuelCard* zone) {
  if (zone->id != MAHA_VAILO)
    return;

  IncrementPermStage(zone);
  Duel_ShowEffectText(MAHA_VAILO);
  Duel_RefreshMonsterStatOverlays();
}
