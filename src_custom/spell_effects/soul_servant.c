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

static void SOUL_SERVANT_ResolveBody(void)
{
  Duel_ShowEffectText(SOUL_SERVANT);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSOUL_SERVANT(void)
{
  if (Duel_TryResolveSpellThroughTraps(SOUL_SERVANT, SOUL_SERVANT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
