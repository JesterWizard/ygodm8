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

static void EN_SHUFFLE_ResolveBody(void)
{
  Duel_ShowEffectText(EN_SHUFFLE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectEN_SHUFFLE(void)
{
  if (Duel_TryResolveSpellThroughTraps(EN_SHUFFLE, EN_SHUFFLE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
