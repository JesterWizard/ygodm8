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

static void ANCIENT_GEAR_ADVANCE_ResolveBody(void)
{
  Duel_ShowEffectText(ANCIENT_GEAR_ADVANCE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectANCIENT_GEAR_ADVANCE(void)
{
  if (Duel_TryResolveSpellThroughTraps(ANCIENT_GEAR_ADVANCE, ANCIENT_GEAR_ADVANCE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
