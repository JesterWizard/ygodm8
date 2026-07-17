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

static void THE_MELODY_OF_AWAKENING_DRAGON_ResolveBody(void)
{
  Duel_ShowEffectText(THE_MELODY_OF_AWAKENING_DRAGON);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectTHE_MELODY_OF_AWAKENING_DRAGON(void)
{
  if (Duel_TryResolveSpellThroughTraps(THE_MELODY_OF_AWAKENING_DRAGON, THE_MELODY_OF_AWAKENING_DRAGON_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
