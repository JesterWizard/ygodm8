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

static void SHARE_THE_PAIN_ResolveBody(void)
{
  Duel_ShowEffectText(SHARE_THE_PAIN);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSHARE_THE_PAIN(void)
{
  if (Duel_TryResolveSpellThroughTraps(SHARE_THE_PAIN, SHARE_THE_PAIN_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
