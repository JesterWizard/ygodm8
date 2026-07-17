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

static void TRIANGLE_ECSTASY_SPARK_ResolveBody(void)
{
  Duel_ShowEffectText(TRIANGLE_ECSTASY_SPARK);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectTRIANGLE_ECSTASY_SPARK(void)
{
  if (Duel_TryResolveSpellThroughTraps(TRIANGLE_ECSTASY_SPARK, TRIANGLE_ECSTASY_SPARK_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
