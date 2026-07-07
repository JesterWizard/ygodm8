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

static void HERO_FLASH_ResolveBody(void)
{
  Duel_ShowEffectText(HERO_FLASH);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectHERO_FLASH(void)
{
  if (Duel_TryResolveSpellThroughTraps(HERO_FLASH, HERO_FLASH_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
