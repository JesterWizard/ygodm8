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

static void REALM_OF_LIGHT_ResolveBody(void)
{
  Duel_ShowEffectText(REALM_OF_LIGHT);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectREALM_OF_LIGHT(void)
{
  if (Duel_TryResolveSpellThroughTraps(REALM_OF_LIGHT, REALM_OF_LIGHT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
