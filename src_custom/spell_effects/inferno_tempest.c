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

static void INFERNO_TEMPEST_ResolveBody(void)
{
  Duel_ShowEffectText(INFERNO_TEMPEST);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectINFERNO_TEMPEST(void)
{
  if (Duel_TryResolveSpellThroughTraps(INFERNO_TEMPEST, INFERNO_TEMPEST_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
