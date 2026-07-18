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

static void LIGHT_FORCE_ResolveBody(void)
{
  Duel_ShowEffectText(LIGHT_FORCE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectLIGHT_FORCE(void)
{
  if (Duel_TryResolveSpellThroughTraps(LIGHT_FORCE, LIGHT_FORCE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
