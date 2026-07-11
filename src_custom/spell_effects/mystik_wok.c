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

static void MYSTIK_WOK_ResolveBody(void)
{
  Duel_ShowEffectText(MYSTIK_WOK);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMYSTIK_WOK(void)
{
  if (Duel_TryResolveSpellThroughTraps(MYSTIK_WOK, MYSTIK_WOK_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
