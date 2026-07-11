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

static void THE_CLAW_OF_HERMOS_ResolveBody(void)
{
  Duel_ShowEffectText(THE_CLAW_OF_HERMOS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectTHE_CLAW_OF_HERMOS(void)
{
  if (Duel_TryResolveSpellThroughTraps(THE_CLAW_OF_HERMOS, THE_CLAW_OF_HERMOS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
