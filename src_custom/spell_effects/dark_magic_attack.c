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

static void DARK_MAGIC_ATTACK_ResolveBody(void)
{
  Duel_ShowEffectText(DARK_MAGIC_ATTACK);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectDARK_MAGIC_ATTACK(void)
{
  if (Duel_TryResolveSpellThroughTraps(DARK_MAGIC_ATTACK, DARK_MAGIC_ATTACK_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
