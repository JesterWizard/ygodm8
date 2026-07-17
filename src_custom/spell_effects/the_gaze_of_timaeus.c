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

static void THE_GAZE_OF_TIMAEUS_ResolveBody(void)
{
  Duel_ShowEffectText(THE_GAZE_OF_TIMAEUS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectTHE_GAZE_OF_TIMAEUS(void)
{
  if (Duel_TryResolveSpellThroughTraps(THE_GAZE_OF_TIMAEUS, THE_GAZE_OF_TIMAEUS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
