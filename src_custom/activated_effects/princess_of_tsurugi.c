#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

void __attribute__((section(".append_text"))) ActivatePrincessOfTsurugiEffect(void)
{
  u8 i;
  u16 damage = 0;
  u8 target = (WhoseTurn() == DUEL_PLAYER) ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    if (gTurnZones[0][i]->id != CARD_NONE)
      damage += 500;
  }

  if (damage > 0) {
    if (Duel_ChangeLp(target, -(s32)damage, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_ShowEffectTextTyped(PRINCESS_OF_TSURUGI, 2);
}
