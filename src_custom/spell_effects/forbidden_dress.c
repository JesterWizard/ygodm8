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

static void FORBIDDEN_DRESS_ResolveBody(void)
{
  Duel_ShowEffectText(FORBIDDEN_DRESS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectFORBIDDEN_DRESS(void)
{
  if (Duel_TryResolveSpellThroughTraps(FORBIDDEN_DRESS, FORBIDDEN_DRESS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
