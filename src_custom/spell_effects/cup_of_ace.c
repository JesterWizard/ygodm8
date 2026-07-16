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

static void CUP_OF_ACE_ResolveBody(void)
{
  Duel_ShowEffectText(CUP_OF_ACE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectCUP_OF_ACE(void)
{
  if (Duel_TryResolveSpellThroughTraps(CUP_OF_ACE, CUP_OF_ACE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
