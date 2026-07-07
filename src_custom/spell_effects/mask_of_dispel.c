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

static void MASK_OF_DISPEL_ResolveBody(void)
{
  Duel_ShowEffectText(MASK_OF_DISPEL);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMASK_OF_DISPEL(void)
{
  if (Duel_TryResolveSpellThroughTraps(MASK_OF_DISPEL, MASK_OF_DISPEL_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
