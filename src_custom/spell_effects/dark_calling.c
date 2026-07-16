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

static void DARK_CALLING_ResolveBody(void)
{
  Duel_ShowEffectText(DARK_CALLING);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectDARK_CALLING(void)
{
  if (Duel_TryResolveSpellThroughTraps(DARK_CALLING, DARK_CALLING_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
