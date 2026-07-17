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

static void ULTRA_POLYMERIZATION_ResolveBody(void)
{
  Duel_ShowEffectText(ULTRA_POLYMERIZATION);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectULTRA_POLYMERIZATION(void)
{
  if (Duel_TryResolveSpellThroughTraps(ULTRA_POLYMERIZATION, ULTRA_POLYMERIZATION_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
