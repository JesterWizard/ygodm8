#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "second_coin_toss.h"

#define CUP_OF_ACE_DRAW_COUNT 2

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void CUP_OF_ACE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 drawDuelist;

  Duel_ShowEffectText(CUP_OF_ACE);

  if (IsDuelOver() == TRUE)
    return;

  /* Heads: active draws; Tails: opponent draws. Same coin convention as blowback_dragon. */
  if (SecondCoinToss_Flip(FixedDuelistForTurnDuelist(ACTIVE_DUELIST)))
    drawDuelist = ACTIVE_DUELIST;
  else
    drawDuelist = INACTIVE_DUELIST;

  if (Duel_DrawCards(drawDuelist, CUP_OF_ACE_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectCUP_OF_ACE(void)
{
  if (Duel_TryResolveSpellThroughTraps(CUP_OF_ACE, CUP_OF_ACE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
