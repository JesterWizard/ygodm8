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

static void CONTACT_GATE_ResolveBody(void)
{
  Duel_ShowEffectText(CONTACT_GATE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectCONTACT_GATE(void)
{
  if (Duel_TryResolveSpellThroughTraps(CONTACT_GATE, CONTACT_GATE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
