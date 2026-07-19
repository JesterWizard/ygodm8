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

static void MORPHTRONIC_CORD_ResolveBody(void)
{
  Duel_ShowEffectText(MORPHTRONIC_CORD);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMORPHTRONIC_CORD(void)
{
  if (Duel_TryResolveSpellThroughTraps(MORPHTRONIC_CORD, MORPHTRONIC_CORD_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
