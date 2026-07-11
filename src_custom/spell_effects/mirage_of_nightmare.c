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

static void MIRAGE_OF_NIGHTMARE_ResolveBody(void)
{
  Duel_ShowEffectText(MIRAGE_OF_NIGHTMARE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMIRAGE_OF_NIGHTMARE(void)
{
  if (Duel_TryResolveSpellThroughTraps(MIRAGE_OF_NIGHTMARE, MIRAGE_OF_NIGHTMARE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
