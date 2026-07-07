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

static void FIRES_OF_DOOMSDAY_ResolveBody(void)
{
  Duel_ShowEffectText(FIRES_OF_DOOMSDAY);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectFIRES_OF_DOOMSDAY(void)
{
  if (Duel_TryResolveSpellThroughTraps(FIRES_OF_DOOMSDAY, FIRES_OF_DOOMSDAY_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
