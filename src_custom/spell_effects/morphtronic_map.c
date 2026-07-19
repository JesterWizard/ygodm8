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

static void MORPHTRONIC_MAP_ResolveBody(void)
{
  Duel_ShowEffectText(MORPHTRONIC_MAP);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMORPHTRONIC_MAP(void)
{
  if (Duel_TryResolveSpellThroughTraps(MORPHTRONIC_MAP, MORPHTRONIC_MAP_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
