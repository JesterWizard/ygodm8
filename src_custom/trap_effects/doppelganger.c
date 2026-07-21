#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "doppelganger.h"
#include "duel_helpers.h"

static void ActivateDOPPELGANGERZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, DOPPELGANGER) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateDOPPELGANGEROnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(DOPPELGANGER, ActivateDOPPELGANGERZone);
}

void TryApplyDoppelgangerAfterEffectDamage(u8 damagedFixedDuelist, u16 damage)
{
  u8 oppTurn;

  if (damage == 0 || IsDuelOver() == TRUE)
    return;

  if (Duel_FindBackrowCard(damagedFixedDuelist, DOPPELGANGER, TRUE) == NULL)
    return;

  oppTurn = (gTurnDuelistBattleState[ACTIVE_DUELIST]
                 == &gDuel.duelistbattleState[damagedFixedDuelist])
                ? INACTIVE_DUELIST
                : ACTIVE_DUELIST;

  Duel_ShowEffectText(DOPPELGANGER);
  Duel_ChangeLp(oppTurn, -(s32)damage, TRUE);
}
