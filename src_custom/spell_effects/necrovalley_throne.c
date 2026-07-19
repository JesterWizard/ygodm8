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

static void NECROVALLEY_THRONE_ResolveBody(void)
{
  Duel_ShowEffectText(NECROVALLEY_THRONE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectNECROVALLEY_THRONE(void)
{
  if (Duel_TryResolveSpellThroughTraps(NECROVALLEY_THRONE, NECROVALLEY_THRONE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
