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

static void INFECTED_MAIL_ResolveBody(void)
{
  Duel_ShowEffectText(INFECTED_MAIL);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectINFECTED_MAIL(void)
{
  if (Duel_TryResolveSpellThroughTraps(INFECTED_MAIL, INFECTED_MAIL_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
