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

static void MAGICAL_STONE_EXCAVATION_ResolveBody(void)
{
  Duel_ShowEffectText(MAGICAL_STONE_EXCAVATION);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMAGICAL_STONE_EXCAVATION(void)
{
  if (Duel_TryResolveSpellThroughTraps(MAGICAL_STONE_EXCAVATION, MAGICAL_STONE_EXCAVATION_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
