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

static void CONTINUOUS_DESTRUCTION_PUNCH_ResolveBody(void)
{
  Duel_ShowEffectText(CONTINUOUS_DESTRUCTION_PUNCH);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectCONTINUOUS_DESTRUCTION_PUNCH(void)
{
  if (Duel_TryResolveSpellThroughTraps(CONTINUOUS_DESTRUCTION_PUNCH, CONTINUOUS_DESTRUCTION_PUNCH_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
