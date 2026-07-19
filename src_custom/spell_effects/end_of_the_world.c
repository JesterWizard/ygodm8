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

static void END_OF_THE_WORLD_ResolveBody(void)
{
  Duel_ShowEffectText(END_OF_THE_WORLD);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectEND_OF_THE_WORLD(void)
{
  if (Duel_TryResolveSpellThroughTraps(END_OF_THE_WORLD, END_OF_THE_WORLD_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
