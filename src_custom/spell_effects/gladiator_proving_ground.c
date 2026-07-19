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

static void GLADIATOR_PROVING_GROUND_ResolveBody(void)
{
  Duel_ShowEffectText(GLADIATOR_PROVING_GROUND);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectGLADIATOR_PROVING_GROUND(void)
{
  if (Duel_TryResolveSpellThroughTraps(GLADIATOR_PROVING_GROUND, GLADIATOR_PROVING_GROUND_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
