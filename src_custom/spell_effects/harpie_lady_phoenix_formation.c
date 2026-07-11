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

static void HARPIE_LADY_PHOENIX_FORMATION_ResolveBody(void)
{
  Duel_ShowEffectText(HARPIE_LADY_PHOENIX_FORMATION);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectHARPIE_LADY_PHOENIX_FORMATION(void)
{
  if (Duel_TryResolveSpellThroughTraps(HARPIE_LADY_PHOENIX_FORMATION, HARPIE_LADY_PHOENIX_FORMATION_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
