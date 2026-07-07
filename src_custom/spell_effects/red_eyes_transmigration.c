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

static void RED_EYES_TRANSMIGRATION_ResolveBody(void)
{
  Duel_ShowEffectText(RED_EYES_TRANSMIGRATION);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectRED_EYES_TRANSMIGRATION(void)
{
  if (Duel_TryResolveSpellThroughTraps(RED_EYES_TRANSMIGRATION, RED_EYES_TRANSMIGRATION_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
