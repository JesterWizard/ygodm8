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

static void INSTANT_CONTACT_ResolveBody(void)
{
  Duel_ShowEffectText(INSTANT_CONTACT);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectINSTANT_CONTACT(void)
{
  if (Duel_TryResolveSpellThroughTraps(INSTANT_CONTACT, INSTANT_CONTACT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
