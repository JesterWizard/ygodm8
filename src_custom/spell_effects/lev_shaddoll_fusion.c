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

static void LEV_SHADDOLL_FUSION_ResolveBody(void)
{
  Duel_ShowEffectText(LEV_SHADDOLL_FUSION);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectLEV_SHADDOLL_FUSION(void)
{
  if (Duel_TryResolveSpellThroughTraps(LEV_SHADDOLL_FUSION, LEV_SHADDOLL_FUSION_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
