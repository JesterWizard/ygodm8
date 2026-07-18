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

static void COCOON_REBIRTH_ResolveBody(void)
{
  Duel_ShowEffectText(COCOON_REBIRTH);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectCOCOON_REBIRTH(void)
{
  if (Duel_TryResolveSpellThroughTraps(COCOON_REBIRTH, COCOON_REBIRTH_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
