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

static void SPELL_CHRONICLE_ResolveBody(void)
{
  Duel_ShowEffectText(SPELL_CHRONICLE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSPELL_CHRONICLE(void)
{
  if (Duel_TryResolveSpellThroughTraps(SPELL_CHRONICLE, SPELL_CHRONICLE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
