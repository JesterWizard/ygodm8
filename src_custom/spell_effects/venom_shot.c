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

static void VENOM_SHOT_ResolveBody(void)
{
  Duel_ShowEffectText(VENOM_SHOT);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectVENOM_SHOT(void)
{
  if (Duel_TryResolveSpellThroughTraps(VENOM_SHOT, VENOM_SHOT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
