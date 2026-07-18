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

static void SOLAR_RECHARGE_ResolveBody(void)
{
  Duel_ShowEffectText(SOLAR_RECHARGE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSOLAR_RECHARGE(void)
{
  if (Duel_TryResolveSpellThroughTraps(SOLAR_RECHARGE, SOLAR_RECHARGE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
