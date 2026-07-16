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

static void SILVERS_CRY_ResolveBody(void)
{
  Duel_ShowEffectText(SILVERS_CRY);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSILVERS_CRY(void)
{
  if (Duel_TryResolveSpellThroughTraps(SILVERS_CRY, SILVERS_CRY_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
