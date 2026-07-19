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

static void AMAZONESS_VILLAGE_ResolveBody(void)
{
  Duel_ShowEffectText(AMAZONESS_VILLAGE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectAMAZONESS_VILLAGE(void)
{
  if (Duel_TryResolveSpellThroughTraps(AMAZONESS_VILLAGE, AMAZONESS_VILLAGE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
