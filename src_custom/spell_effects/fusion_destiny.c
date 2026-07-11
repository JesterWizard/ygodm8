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

static void FUSION_DESTINY_ResolveBody(void)
{
  Duel_ShowEffectText(FUSION_DESTINY);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectFUSION_DESTINY(void)
{
  if (Duel_TryResolveSpellThroughTraps(FUSION_DESTINY, FUSION_DESTINY_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
