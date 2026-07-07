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

static void BURDEN_OF_THE_MIGHTY_ResolveBody(void)
{
  Duel_ShowEffectText(BURDEN_OF_THE_MIGHTY);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectBURDEN_OF_THE_MIGHTY(void)
{
  if (Duel_TryResolveSpellThroughTraps(BURDEN_OF_THE_MIGHTY, BURDEN_OF_THE_MIGHTY_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
