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

static void TWLIGHT_TWIN_DRAGONS_ResolveBody(void)
{
  Duel_ShowEffectText(TWLIGHT_TWIN_DRAGONS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectTWLIGHT_TWIN_DRAGONS(void)
{
  if (Duel_TryResolveSpellThroughTraps(TWLIGHT_TWIN_DRAGONS, TWLIGHT_TWIN_DRAGONS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
