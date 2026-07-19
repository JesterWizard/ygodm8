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

static void SHINING_SARCOPHAGUS_ResolveBody(void)
{
  Duel_ShowEffectText(SHINING_SARCOPHAGUS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSHINING_SARCOPHAGUS(void)
{
  if (Duel_TryResolveSpellThroughTraps(SHINING_SARCOPHAGUS, SHINING_SARCOPHAGUS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
