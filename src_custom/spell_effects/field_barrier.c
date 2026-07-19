#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static void FIELD_BARRIER_ResolveBody(void)
{
  Duel_ShowEffectText(FIELD_BARRIER);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectFIELD_BARRIER(void)
{
  if (Duel_TryResolveSpellThroughTraps(FIELD_BARRIER, FIELD_BARRIER_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
