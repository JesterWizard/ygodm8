#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "graveyard_effects.h"

static u8 TurnDuelistForGraveyardRow(u8 turnRow)
{
  if (turnRow == 7)
    return INACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static u8 CanSpecialSummonDespair(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

unsigned char ShouldActivateDESPAIR_FROM_THE_DARK(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != DESPAIR_FROM_THE_DARK)
    return FALSE;

  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != DESPAIR_FROM_THE_DARK)
      return FALSE;
    turnDuelist = INACTIVE_DUELIST;
  } else {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != DESPAIR_FROM_THE_DARK)
      return FALSE;
    turnDuelist = ACTIVE_DUELIST;
  }

  /* opp hand/Deck send by card effect not tracked — GY-top SS only. */
  return CanSpecialSummonDespair(turnDuelist);
}

void ActivateDESPAIR_FROM_THE_DARK(void)
{
  u8 turnDuelist;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  turnDuelist = TurnDuelistForGraveyardRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(DESPAIR_FROM_THE_DARK, 8);
  if (IsDuelOver() == TRUE)
    return;

  Duel_SpecialSummonFromGrave(turnDuelist, DESPAIR_FROM_THE_DARK, opts);
}
