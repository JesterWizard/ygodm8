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

static void CELESTIAL_SWORD_EATOS_ResolveBody(void)
{
  Duel_ShowEffectText(CELESTIAL_SWORD_EATOS);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectCELESTIAL_SWORD_EATOS(void)
{
  if (Duel_TryResolveSpellThroughTraps(CELESTIAL_SWORD_EATOS, CELESTIAL_SWORD_EATOS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
