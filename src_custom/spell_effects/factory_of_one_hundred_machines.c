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

static void FACTORY_OF_ONE_HUNDRED_MACHINES_ResolveBody(void)
{
  Duel_ShowEffectText(FACTORY_OF_ONE_HUNDRED_MACHINES);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectFACTORY_OF_ONE_HUNDRED_MACHINES(void)
{
  if (Duel_TryResolveSpellThroughTraps(FACTORY_OF_ONE_HUNDRED_MACHINES, FACTORY_OF_ONE_HUNDRED_MACHINES_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
