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

static void MONSTER_GATE_ResolveBody(void)
{
  Duel_ShowEffectText(MONSTER_GATE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMONSTER_GATE(void)
{
  if (Duel_TryResolveSpellThroughTraps(MONSTER_GATE, MONSTER_GATE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
