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

static void ANCIENT_GEAR_TANK_ResolveBody(void)
{
  Duel_ShowEffectText(ANCIENT_GEAR_TANK);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectANCIENT_GEAR_TANK(void)
{
  if (Duel_TryResolveSpellThroughTraps(ANCIENT_GEAR_TANK, ANCIENT_GEAR_TANK_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
