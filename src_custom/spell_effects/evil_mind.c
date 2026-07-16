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

static void EVIL_MIND_ResolveBody(void)
{
  Duel_ShowEffectText(EVIL_MIND);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectEVIL_MIND(void)
{
  if (Duel_TryResolveSpellThroughTraps(EVIL_MIND, EVIL_MIND_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
