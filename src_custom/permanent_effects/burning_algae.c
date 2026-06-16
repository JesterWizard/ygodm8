#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define BURNING_ALGAE_GY_HEAL 1000

static u8 GraveyardMatchesBurningAlgae(u8 turnRow)
{
  if (turnRow == 7)
    return gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == BURNING_ALGAE;

  return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == BURNING_ALGAE;
}

unsigned char ShouldActivateBurningAlgae(void)
{
  if (gActiveEffect.cardId != BURNING_ALGAE)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  return GraveyardMatchesBurningAlgae(gActiveEffect.turnRow);
}

void ActivateBurningAlgae(void)
{
  u8 opponent = (gActiveEffect.turnRow == 6) ? INACTIVE_DUELIST : ACTIVE_DUELIST;
  u8 turnDuelist = (gActiveEffect.turnRow == 6) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  Duel_ShowEffectTextTyped(BURNING_ALGAE, 8);

  if (Duel_ChangeLp(opponent, BURNING_ALGAE_GY_HEAL, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  GetGraveCardAndClearGrave(turnDuelist);
}
