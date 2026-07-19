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

static void GEARTOWN_ResolveBody(void)
{
  Duel_ShowEffectText(GEARTOWN);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectGEARTOWN(void)
{
  if (Duel_TryResolveSpellThroughTraps(GEARTOWN, GEARTOWN_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
