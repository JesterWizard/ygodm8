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

static void SUPREME_KINGS_CASTLE_ResolveBody(void)
{
  Duel_ShowEffectText(SUPREME_KINGS_CASTLE);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectSUPREME_KINGS_CASTLE(void)
{
  if (Duel_TryResolveSpellThroughTraps(SUPREME_KINGS_CASTLE, SUPREME_KINGS_CASTLE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
