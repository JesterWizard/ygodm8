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

static void GLADIATOR_BEASTS_BATTLE_GLADIUS_ResolveBody(void)
{
  Duel_ShowEffectText(GLADIATOR_BEASTS_BATTLE_GLADIUS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectGLADIATOR_BEASTS_BATTLE_GLADIUS(void)
{
  if (Duel_TryResolveSpellThroughTraps(GLADIATOR_BEASTS_BATTLE_GLADIUS, GLADIATOR_BEASTS_BATTLE_GLADIUS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
