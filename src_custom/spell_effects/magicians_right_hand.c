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

static void MAGICIANS_RIGHT_HAND_ResolveBody(void)
{
  Duel_ShowEffectText(MAGICIANS_RIGHT_HAND);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMAGICIANS_RIGHT_HAND(void)
{
  if (Duel_TryResolveSpellThroughTraps(MAGICIANS_RIGHT_HAND, MAGICIANS_RIGHT_HAND_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
