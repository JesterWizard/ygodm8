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

static void CHICKEN_GAME_ResolveBody(void)
{
  Duel_ShowEffectText(CHICKEN_GAME);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectCHICKEN_GAME(void)
{
  if (Duel_TryResolveSpellThroughTraps(CHICKEN_GAME, CHICKEN_GAME_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
