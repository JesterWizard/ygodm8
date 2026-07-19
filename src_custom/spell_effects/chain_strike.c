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

static void CHAIN_STRIKE_ResolveBody(void)
{
  Duel_ShowEffectText(CHAIN_STRIKE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectCHAIN_STRIKE(void)
{
  if (Duel_TryResolveSpellThroughTraps(CHAIN_STRIKE, CHAIN_STRIKE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
