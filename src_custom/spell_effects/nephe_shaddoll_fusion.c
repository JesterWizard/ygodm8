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

static void NEPHE_SHADDOLL_FUSION_ResolveBody(void)
{
  Duel_ShowEffectText(NEPHE_SHADDOLL_FUSION);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectNEPHE_SHADDOLL_FUSION(void)
{
  if (Duel_TryResolveSpellThroughTraps(NEPHE_SHADDOLL_FUSION, NEPHE_SHADDOLL_FUSION_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
