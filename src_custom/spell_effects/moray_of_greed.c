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

static void MORAY_OF_GREED_ResolveBody(void)
{
  Duel_ShowEffectText(MORAY_OF_GREED);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMORAY_OF_GREED(void)
{
  if (Duel_TryResolveSpellThroughTraps(MORAY_OF_GREED, MORAY_OF_GREED_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
