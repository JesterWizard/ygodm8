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

static void ALLURE_OF_DARKNESS_ResolveBody(void)
{
  Duel_ShowEffectText(ALLURE_OF_DARKNESS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectALLURE_OF_DARKNESS(void)
{
  if (Duel_TryResolveSpellThroughTraps(ALLURE_OF_DARKNESS, ALLURE_OF_DARKNESS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
