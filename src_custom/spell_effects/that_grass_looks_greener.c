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

static void THAT_GRASS_LOOKS_GREENER_ResolveBody(void)
{
  Duel_ShowEffectText(THAT_GRASS_LOOKS_GREENER);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectTHAT_GRASS_LOOKS_GREENER(void)
{
  if (Duel_TryResolveSpellThroughTraps(THAT_GRASS_LOOKS_GREENER, THAT_GRASS_LOOKS_GREENER_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
