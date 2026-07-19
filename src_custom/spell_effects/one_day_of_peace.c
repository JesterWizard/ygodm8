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

static void ONE_DAY_OF_PEACE_ResolveBody(void)
{
  Duel_ShowEffectText(ONE_DAY_OF_PEACE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectONE_DAY_OF_PEACE(void)
{
  if (Duel_TryResolveSpellThroughTraps(ONE_DAY_OF_PEACE, ONE_DAY_OF_PEACE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
