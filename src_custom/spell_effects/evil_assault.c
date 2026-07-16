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

static void EVIL_ASSAULT_ResolveBody(void)
{
  Duel_ShowEffectText(EVIL_ASSAULT);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectEVIL_ASSAULT(void)
{
  if (Duel_TryResolveSpellThroughTraps(EVIL_ASSAULT, EVIL_ASSAULT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
