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

static void HYSTERIC_SIGN_ResolveBody(void)
{
  Duel_ShowEffectText(HYSTERIC_SIGN);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectHYSTERIC_SIGN(void)
{
  if (Duel_TryResolveSpellThroughTraps(HYSTERIC_SIGN, HYSTERIC_SIGN_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
