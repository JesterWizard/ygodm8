#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define DARKLORD_MARIE_STANDBY_HEAL 200

void ActivateDarklordMarieTurnEffect(void)
{
  Duel_ShowEffectTextTyped(DARKLORD_MARIE, 9);

  if (Duel_ChangeLp(WhoseTurn(), DARKLORD_MARIE_STANDBY_HEAL, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}
