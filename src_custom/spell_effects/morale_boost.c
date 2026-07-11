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

static void MORALE_BOOST_ResolveBody(void)
{
  Duel_ShowEffectText(MORALE_BOOST);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMORALE_BOOST(void)
{
  if (Duel_TryResolveSpellThroughTraps(MORALE_BOOST, MORALE_BOOST_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
