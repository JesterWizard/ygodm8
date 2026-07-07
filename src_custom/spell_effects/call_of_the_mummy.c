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

static void CALL_OF_THE_MUMMY_ResolveBody(void)
{
  Duel_ShowEffectText(CALL_OF_THE_MUMMY);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectCALL_OF_THE_MUMMY(void)
{
  if (Duel_TryResolveSpellThroughTraps(CALL_OF_THE_MUMMY, CALL_OF_THE_MUMMY_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
