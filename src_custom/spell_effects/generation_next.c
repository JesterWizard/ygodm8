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

static void GENERATION_NEXT_ResolveBody(void)
{
  Duel_ShowEffectText(GENERATION_NEXT);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectGENERATION_NEXT(void)
{
  if (Duel_TryResolveSpellThroughTraps(GENERATION_NEXT, GENERATION_NEXT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
