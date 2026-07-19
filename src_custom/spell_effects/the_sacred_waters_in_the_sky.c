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

static void THE_SACRED_WATERS_IN_THE_SKY_ResolveBody(void)
{
  Duel_ShowEffectText(THE_SACRED_WATERS_IN_THE_SKY);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectTHE_SACRED_WATERS_IN_THE_SKY(void)
{
  if (Duel_TryResolveSpellThroughTraps(THE_SACRED_WATERS_IN_THE_SKY, THE_SACRED_WATERS_IN_THE_SKY_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
