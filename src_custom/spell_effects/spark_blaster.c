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

static void SPARK_BLASTER_ResolveBody(void)
{
  Duel_ShowEffectText(SPARK_BLASTER);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSPARK_BLASTER(void)
{
  if (Duel_TryResolveSpellThroughTraps(SPARK_BLASTER, SPARK_BLASTER_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
