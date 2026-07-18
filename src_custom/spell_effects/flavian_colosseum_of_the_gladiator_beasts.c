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

static void FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS_ResolveBody(void)
{
  Duel_ShowEffectText(FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectFLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS(void)
{
  if (Duel_TryResolveSpellThroughTraps(FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS, FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
