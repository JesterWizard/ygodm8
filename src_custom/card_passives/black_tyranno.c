#include "global.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "black_tyranno.h"

u8 CanBlackTyrannoAttackDirectly(u16 cardId) {
  u8 i;
  u8 hasMonster = FALSE;

  if (cardId != BLACK_TYRANNO)
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[1][i]->id == CARD_NONE)
      continue;
    hasMonster = TRUE;
    if (!gTurnZones[1][i]->isDefending)
      return FALSE;
  }

  return hasMonster;
}

void TryShowBlackTyrannoDirectAttackText(u16 cardId) {
  if (CanBlackTyrannoAttackDirectly(cardId))
    ActivatePermanentEffectCardText(BLACK_TYRANNO);
}
