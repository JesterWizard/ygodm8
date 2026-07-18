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

static void NEO_SPACE_ResolveBody(void)
{
  Duel_ShowEffectText(NEO_SPACE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectNEO_SPACE(void)
{
  if (Duel_TryResolveSpellThroughTraps(NEO_SPACE, NEO_SPACE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
