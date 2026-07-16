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

static void FUSION_DEPLOYMENT_ResolveBody(void)
{
  Duel_ShowEffectText(FUSION_DEPLOYMENT);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectFUSION_DEPLOYMENT(void)
{
  if (Duel_TryResolveSpellThroughTraps(FUSION_DEPLOYMENT, FUSION_DEPLOYMENT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
