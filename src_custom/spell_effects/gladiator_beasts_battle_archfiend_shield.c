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

static void GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD_ResolveBody(void)
{
  Duel_ShowEffectText(GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectGLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD(void)
{
  if (Duel_TryResolveSpellThroughTraps(GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD, GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
