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

static void MYSTIC_WOK_ResolveBody(void)
{
  Duel_ShowEffectText(MYSTIC_WOK);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMYSTIC_WOK(void)
{
  if (Duel_TryResolveSpellThroughTraps(MYSTIC_WOK, MYSTIC_WOK_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
