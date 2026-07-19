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

static void SUMMONERS_ART_ResolveBody(void)
{
  Duel_ShowEffectText(SUMMONERS_ART);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSUMMONERS_ART(void)
{
  if (Duel_TryResolveSpellThroughTraps(SUMMONERS_ART, SUMMONERS_ART_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
