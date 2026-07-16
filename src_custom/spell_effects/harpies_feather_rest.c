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

static void HARPIES_FEATHER_REST_ResolveBody(void)
{
  Duel_ShowEffectText(HARPIES_FEATHER_REST);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectHARPIES_FEATHER_REST(void)
{
  if (Duel_TryResolveSpellThroughTraps(HARPIES_FEATHER_REST, HARPIES_FEATHER_REST_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
