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

static void INSECT_IMITATION_ResolveBody(void)
{
  Duel_ShowEffectText(INSECT_IMITATION);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectINSECT_IMITATION(void)
{
  if (Duel_TryResolveSpellThroughTraps(INSECT_IMITATION, INSECT_IMITATION_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
