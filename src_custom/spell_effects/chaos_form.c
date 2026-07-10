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

static void CHAOS_FORM_ResolveBody(void)
{
  Duel_ShowEffectText(CHAOS_FORM);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectCHAOS_FORM(void)
{
  if (Duel_TryResolveSpellThroughTraps(CHAOS_FORM, CHAOS_FORM_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
