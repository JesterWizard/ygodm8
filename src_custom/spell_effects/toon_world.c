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

static void TOON_WORLD_ResolveBody(void)
{
  Duel_ShowEffectText(TOON_WORLD);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectTOON_WORLD(void)
{
  if (Duel_TryResolveSpellThroughTraps(TOON_WORLD, TOON_WORLD_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
