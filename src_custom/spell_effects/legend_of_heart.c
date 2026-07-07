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

static void LEGEND_OF_HEART_ResolveBody(void)
{
  Duel_ShowEffectText(LEGEND_OF_HEART);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectLEGEND_OF_HEART(void)
{
  if (Duel_TryResolveSpellThroughTraps(LEGEND_OF_HEART, LEGEND_OF_HEART_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
