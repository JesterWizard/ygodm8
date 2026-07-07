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

static void EMERGENCY_PROVISIONS_ResolveBody(void)
{
  Duel_ShowEffectText(EMERGENCY_PROVISIONS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectEMERGENCY_PROVISIONS(void)
{
  if (Duel_TryResolveSpellThroughTraps(EMERGENCY_PROVISIONS, EMERGENCY_PROVISIONS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
