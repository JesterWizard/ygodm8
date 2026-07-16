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

static void DARK_MAGICAL_CIRCLE_ResolveBody(void)
{
  Duel_ShowEffectText(DARK_MAGICAL_CIRCLE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectDARK_MAGICAL_CIRCLE(void)
{
  if (Duel_TryResolveSpellThroughTraps(DARK_MAGICAL_CIRCLE, DARK_MAGICAL_CIRCLE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
