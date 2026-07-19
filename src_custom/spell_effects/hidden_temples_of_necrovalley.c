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

static void HIDDEN_TEMPLES_OF_NECROVALLEY_ResolveBody(void)
{
  Duel_ShowEffectText(HIDDEN_TEMPLES_OF_NECROVALLEY);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectHIDDEN_TEMPLES_OF_NECROVALLEY(void)
{
  if (Duel_TryResolveSpellThroughTraps(HIDDEN_TEMPLES_OF_NECROVALLEY, HIDDEN_TEMPLES_OF_NECROVALLEY_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
