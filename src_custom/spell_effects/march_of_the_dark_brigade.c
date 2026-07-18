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

static void MARCH_OF_THE_DARK_BRIGADE_ResolveBody(void)
{
  Duel_ShowEffectText(MARCH_OF_THE_DARK_BRIGADE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMARCH_OF_THE_DARK_BRIGADE(void)
{
  if (Duel_TryResolveSpellThroughTraps(MARCH_OF_THE_DARK_BRIGADE, MARCH_OF_THE_DARK_BRIGADE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
