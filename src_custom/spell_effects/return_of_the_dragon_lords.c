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

static void RETURN_OF_THE_DRAGON_LORDS_ResolveBody(void)
{
  Duel_ShowEffectText(RETURN_OF_THE_DRAGON_LORDS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectRETURN_OF_THE_DRAGON_LORDS(void)
{
  if (Duel_TryResolveSpellThroughTraps(RETURN_OF_THE_DRAGON_LORDS, RETURN_OF_THE_DRAGON_LORDS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
