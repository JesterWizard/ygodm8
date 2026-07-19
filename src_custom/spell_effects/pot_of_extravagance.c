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

static void POT_OF_EXTRAVAGANCE_ResolveBody(void)
{
  Duel_ShowEffectText(POT_OF_EXTRAVAGANCE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectPOT_OF_EXTRAVAGANCE(void)
{
  if (Duel_TryResolveSpellThroughTraps(POT_OF_EXTRAVAGANCE, POT_OF_EXTRAVAGANCE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
