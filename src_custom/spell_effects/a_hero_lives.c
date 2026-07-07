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

static void A_HERO_LIVES_ResolveBody(void)
{
  Duel_ShowEffectText(A_HERO_LIVES);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectA_HERO_LIVES(void)
{
  if (Duel_TryResolveSpellThroughTraps(A_HERO_LIVES, A_HERO_LIVES_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
