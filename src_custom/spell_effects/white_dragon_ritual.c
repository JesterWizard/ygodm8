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

static void WHITE_DRAGON_RITUAL_ResolveBody(void)
{
  Duel_ShowEffectText(WHITE_DRAGON_RITUAL);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectWHITE_DRAGON_RITUAL(void)
{
  if (Duel_TryResolveSpellThroughTraps(WHITE_DRAGON_RITUAL, WHITE_DRAGON_RITUAL_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
