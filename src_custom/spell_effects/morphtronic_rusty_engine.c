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

static void MORPHTRONIC_RUSTY_ENGINE_ResolveBody(void)
{
  Duel_ShowEffectText(MORPHTRONIC_RUSTY_ENGINE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMORPHTRONIC_RUSTY_ENGINE(void)
{
  if (Duel_TryResolveSpellThroughTraps(MORPHTRONIC_RUSTY_ENGINE, MORPHTRONIC_RUSTY_ENGINE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
