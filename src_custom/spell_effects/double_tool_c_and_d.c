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

static void DOUBLE_TOOL_C_AND_D_ResolveBody(void)
{
  Duel_ShowEffectText(DOUBLE_TOOL_C_AND_D);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectDOUBLE_TOOL_C_AND_D(void)
{
  if (Duel_TryResolveSpellThroughTraps(DOUBLE_TOOL_C_AND_D, DOUBLE_TOOL_C_AND_D_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
