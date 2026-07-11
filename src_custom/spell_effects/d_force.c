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

static void D_FORCE_ResolveBody(void)
{
  Duel_ShowEffectText(D_FORCE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectD_FORCE(void)
{
  if (Duel_TryResolveSpellThroughTraps(D_FORCE, D_FORCE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
