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

static void GROUND_COLLAPSE_ResolveBody(void)
{
  Duel_ShowEffectText(GROUND_COLLAPSE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectGROUND_COLLAPSE(void)
{
  if (Duel_TryResolveSpellThroughTraps(GROUND_COLLAPSE, GROUND_COLLAPSE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
