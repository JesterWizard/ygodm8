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

static void ACE_OF_SWORD_ResolveBody(void)
{
  Duel_ShowEffectText(ACE_OF_SWORD);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectACE_OF_SWORD(void)
{
  if (Duel_TryResolveSpellThroughTraps(ACE_OF_SWORD, ACE_OF_SWORD_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
