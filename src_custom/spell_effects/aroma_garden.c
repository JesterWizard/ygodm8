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

static void AROMA_GARDEN_ResolveBody(void)
{
  Duel_ShowEffectText(AROMA_GARDEN);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectAROMA_GARDEN(void)
{
  if (Duel_TryResolveSpellThroughTraps(AROMA_GARDEN, AROMA_GARDEN_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
