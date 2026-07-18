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

static void CHARGE_OF_THE_LIGHT_BRIGADE_ResolveBody(void)
{
  Duel_ShowEffectText(CHARGE_OF_THE_LIGHT_BRIGADE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectCHARGE_OF_THE_LIGHT_BRIGADE(void)
{
  if (Duel_TryResolveSpellThroughTraps(CHARGE_OF_THE_LIGHT_BRIGADE, CHARGE_OF_THE_LIGHT_BRIGADE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
