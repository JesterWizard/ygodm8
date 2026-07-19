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

static void DRAGONS_MIRROR_ResolveBody(void)
{
  Duel_ShowEffectText(DRAGONS_MIRROR);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectDRAGONS_MIRROR(void)
{
  if (Duel_TryResolveSpellThroughTraps(DRAGONS_MIRROR, DRAGONS_MIRROR_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
