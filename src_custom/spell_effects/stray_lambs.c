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

static void STRAY_LAMBS_ResolveBody(void)
{
  Duel_ShowEffectText(STRAY_LAMBS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSTRAY_LAMBS(void)
{
  if (Duel_TryResolveSpellThroughTraps(STRAY_LAMBS, STRAY_LAMBS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
