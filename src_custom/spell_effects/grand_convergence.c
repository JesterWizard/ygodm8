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

static void GRAND_CONVERGENCE_ResolveBody(void)
{
  Duel_ShowEffectText(GRAND_CONVERGENCE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectGRAND_CONVERGENCE(void)
{
  if (Duel_TryResolveSpellThroughTraps(GRAND_CONVERGENCE, GRAND_CONVERGENCE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
