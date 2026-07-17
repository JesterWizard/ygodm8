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

static void SNAKE_RAIN_ResolveBody(void)
{
  Duel_ShowEffectText(SNAKE_RAIN);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSNAKE_RAIN(void)
{
  if (Duel_TryResolveSpellThroughTraps(SNAKE_RAIN, SNAKE_RAIN_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
