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

static void INFERNO_FIRE_BLAST_ResolveBody(void)
{
  Duel_ShowEffectText(INFERNO_FIRE_BLAST);

  /* TODO: implement effect */
}

APPEND_TEXT void EffectINFERNO_FIRE_BLAST(void)
{
  if (Duel_TryResolveSpellThroughTraps(INFERNO_FIRE_BLAST, INFERNO_FIRE_BLAST_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
