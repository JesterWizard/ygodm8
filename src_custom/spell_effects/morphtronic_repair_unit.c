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

static void MORPHTRONIC_REPAIR_UNIT_ResolveBody(void)
{
  Duel_ShowEffectText(MORPHTRONIC_REPAIR_UNIT);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMORPHTRONIC_REPAIR_UNIT(void)
{
  if (Duel_TryResolveSpellThroughTraps(MORPHTRONIC_REPAIR_UNIT, MORPHTRONIC_REPAIR_UNIT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
