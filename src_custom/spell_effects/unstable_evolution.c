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

static void UNSTABLE_EVOLUTION_ResolveBody(void)
{
  Duel_ShowEffectText(UNSTABLE_EVOLUTION);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectUNSTABLE_EVOLUTION(void)
{
  if (Duel_TryResolveSpellThroughTraps(UNSTABLE_EVOLUTION, UNSTABLE_EVOLUTION_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
