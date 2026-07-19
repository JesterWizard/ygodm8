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

static void BIG_EVOLUTION_PILL_ResolveBody(void)
{
  Duel_ShowEffectText(BIG_EVOLUTION_PILL);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectBIG_EVOLUTION_PILL(void)
{
  if (Duel_TryResolveSpellThroughTraps(BIG_EVOLUTION_PILL, BIG_EVOLUTION_PILL_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
