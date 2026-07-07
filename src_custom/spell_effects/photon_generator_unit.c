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

static void PHOTON_GENERATOR_UNIT_ResolveBody(void)
{
  Duel_ShowEffectText(PHOTON_GENERATOR_UNIT);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectPHOTON_GENERATOR_UNIT(void)
{
  if (Duel_TryResolveSpellThroughTraps(PHOTON_GENERATOR_UNIT, PHOTON_GENERATOR_UNIT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
