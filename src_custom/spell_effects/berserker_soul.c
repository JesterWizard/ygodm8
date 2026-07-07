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

static void BERSERKER_SOUL_ResolveBody(void)
{
  Duel_ShowEffectText(BERSERKER_SOUL);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectBERSERKER_SOUL(void)
{
  if (Duel_TryResolveSpellThroughTraps(BERSERKER_SOUL, BERSERKER_SOUL_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
