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

static void WEAPON_CHANGE_ResolveBody(void)
{
  Duel_ShowEffectText(WEAPON_CHANGE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectWEAPON_CHANGE(void)
{
  if (Duel_TryResolveSpellThroughTraps(WEAPON_CHANGE, WEAPON_CHANGE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
