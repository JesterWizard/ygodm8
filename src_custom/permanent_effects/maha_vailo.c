#include "global.h"

void ApplyMahaVailoEquipBonus(struct DuelCard* zone) {
  if (zone->id != MAHA_VAILO)
    return;

  IncrementPermStage(zone);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = MAHA_VAILO;
    ActivateCardEffectText();
  }
}
