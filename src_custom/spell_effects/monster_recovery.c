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

static void MONSTER_RECOVERY_ResolveBody(void)
{
  Duel_ShowEffectText(MONSTER_RECOVERY);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMONSTER_RECOVERY(void)
{
  if (Duel_TryResolveSpellThroughTraps(MONSTER_RECOVERY, MONSTER_RECOVERY_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
