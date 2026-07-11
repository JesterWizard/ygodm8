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

static void POISON_OF_THE_OLD_MAN_ResolveBody(void)
{
  Duel_ShowEffectText(POISON_OF_THE_OLD_MAN);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectPOISON_OF_THE_OLD_MAN(void)
{
  if (Duel_TryResolveSpellThroughTraps(POISON_OF_THE_OLD_MAN, POISON_OF_THE_OLD_MAN_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
