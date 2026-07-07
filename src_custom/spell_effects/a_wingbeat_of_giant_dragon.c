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

static void A_WINGBEAT_OF_GIANT_DRAGON_ResolveBody(void)
{
  Duel_ShowEffectText(A_WINGBEAT_OF_GIANT_DRAGON);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectA_WINGBEAT_OF_GIANT_DRAGON(void)
{
  if (Duel_TryResolveSpellThroughTraps(A_WINGBEAT_OF_GIANT_DRAGON, A_WINGBEAT_OF_GIANT_DRAGON_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
