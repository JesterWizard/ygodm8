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

static void COLD_WAVE_ResolveBody(void)
{
  Duel_ShowEffectText(COLD_WAVE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectCOLD_WAVE(void)
{
  if (Duel_TryResolveSpellThroughTraps(COLD_WAVE, COLD_WAVE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
