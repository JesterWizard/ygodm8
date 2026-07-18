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

static void ARCANA_SPREAD_ResolveBody(void)
{
  Duel_ShowEffectText(ARCANA_SPREAD);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectARCANA_SPREAD(void)
{
  if (Duel_TryResolveSpellThroughTraps(ARCANA_SPREAD, ARCANA_SPREAD_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
