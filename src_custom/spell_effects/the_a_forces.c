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

static void THE_A_FORCES_ResolveBody(void)
{
  Duel_ShowEffectText(THE_A_FORCES);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectTHE_A_FORCES(void)
{
  if (Duel_TryResolveSpellThroughTraps(THE_A_FORCES, THE_A_FORCES_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
