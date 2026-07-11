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

static void DESTINY_DRAW_ResolveBody(void)
{
  Duel_ShowEffectText(DESTINY_DRAW);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectDESTINY_DRAW(void)
{
  if (Duel_TryResolveSpellThroughTraps(DESTINY_DRAW, DESTINY_DRAW_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
