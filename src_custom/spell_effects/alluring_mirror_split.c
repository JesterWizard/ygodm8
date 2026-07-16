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

static void ALLURING_MIRROR_SPLIT_ResolveBody(void)
{
  Duel_ShowEffectText(ALLURING_MIRROR_SPLIT);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectALLURING_MIRROR_SPLIT(void)
{
  if (Duel_TryResolveSpellThroughTraps(ALLURING_MIRROR_SPLIT, ALLURING_MIRROR_SPLIT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
