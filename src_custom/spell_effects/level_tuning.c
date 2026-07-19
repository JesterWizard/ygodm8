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

static void LEVEL_TUNING_ResolveBody(void)
{
  Duel_ShowEffectText(LEVEL_TUNING);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectLEVEL_TUNING(void)
{
  if (Duel_TryResolveSpellThroughTraps(LEVEL_TUNING, LEVEL_TUNING_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
