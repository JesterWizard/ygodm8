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

static void SHARD_OF_GREED_ResolveBody(void)
{
  Duel_ShowEffectText(SHARD_OF_GREED);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSHARD_OF_GREED(void)
{
  if (Duel_TryResolveSpellThroughTraps(SHARD_OF_GREED, SHARD_OF_GREED_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
