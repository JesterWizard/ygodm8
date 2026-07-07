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

static void EVOLUTION_END_BURST_ResolveBody(void)
{
  Duel_ShowEffectText(EVOLUTION_END_BURST);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectEVOLUTION_END_BURST(void)
{
  if (Duel_TryResolveSpellThroughTraps(EVOLUTION_END_BURST, EVOLUTION_END_BURST_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
