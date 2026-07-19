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

static void ROYAL_TRIBUTE_ResolveBody(void)
{
  Duel_ShowEffectText(ROYAL_TRIBUTE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectROYAL_TRIBUTE(void)
{
  if (Duel_TryResolveSpellThroughTraps(ROYAL_TRIBUTE, ROYAL_TRIBUTE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
