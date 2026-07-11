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

static void D_BURST_ResolveBody(void)
{
  Duel_ShowEffectText(D_BURST);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectD_BURST(void)
{
  if (Duel_TryResolveSpellThroughTraps(D_BURST, D_BURST_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
