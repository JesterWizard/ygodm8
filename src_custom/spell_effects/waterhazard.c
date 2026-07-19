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

static void WATERHAZARD_ResolveBody(void)
{
  Duel_ShowEffectText(WATERHAZARD);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectWATERHAZARD(void)
{
  if (Duel_TryResolveSpellThroughTraps(WATERHAZARD, WATERHAZARD_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
