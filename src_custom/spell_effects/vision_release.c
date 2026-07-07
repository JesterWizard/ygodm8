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

static void VISION_RELEASE_ResolveBody(void)
{
  Duel_ShowEffectText(VISION_RELEASE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectVISION_RELEASE(void)
{
  if (Duel_TryResolveSpellThroughTraps(VISION_RELEASE, VISION_RELEASE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
