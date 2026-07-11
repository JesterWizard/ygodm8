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

static void MAUSOLEUM_OF_THE_EMPEROR_ResolveBody(void)
{
  Duel_ShowEffectText(MAUSOLEUM_OF_THE_EMPEROR);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectMAUSOLEUM_OF_THE_EMPEROR(void)
{
  if (Duel_TryResolveSpellThroughTraps(MAUSOLEUM_OF_THE_EMPEROR, MAUSOLEUM_OF_THE_EMPEROR_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
