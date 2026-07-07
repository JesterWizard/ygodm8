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

static void SECOND_COIN_TOSS_ResolveBody(void)
{
  Duel_ShowEffectText(SECOND_COIN_TOSS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSECOND_COIN_TOSS(void)
{
  if (Duel_TryResolveSpellThroughTraps(SECOND_COIN_TOSS, SECOND_COIN_TOSS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
