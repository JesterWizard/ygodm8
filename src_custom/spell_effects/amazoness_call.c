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

static void AMAZONESS_CALL_ResolveBody(void)
{
  Duel_ShowEffectText(AMAZONESS_CALL);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectAMAZONESS_CALL(void)
{
  if (Duel_TryResolveSpellThroughTraps(AMAZONESS_CALL, AMAZONESS_CALL_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
