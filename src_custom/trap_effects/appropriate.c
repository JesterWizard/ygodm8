#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "drop_off.h"
#include "duel_helpers.h"
#include "appropriate.h"

static void ActivateAPPROPRIATEZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, APPROPRIATE) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateAPPROPRIATEOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(APPROPRIATE, ActivateAPPROPRIATEZone);
}

void TryApplyAppropriateOnDraw(u8 drawerFixedDuelist)
{
  u8 controller;
  u8 turnDuelist;

  /* Printed: activate when opp draws outside Draw Phase; then each such draw → you draw 2.
   * Face-up continuous stand-in: whenever opp draws outside normal Draw Phase draws. */
  if (gDrawPhaseNormalDrawActive)
    return;

  if (drawerFixedDuelist != DUEL_PLAYER && drawerFixedDuelist != DUEL_OPPONENT)
    return;

  controller = drawerFixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  if (Duel_FindBackrowCard(controller, APPROPRIATE, TRUE) == NULL)
    return;

  turnDuelist = (gTurnDuelistBattleState[ACTIVE_DUELIST]
                     == &gDuel.duelistbattleState[controller])
                    ? ACTIVE_DUELIST
                    : INACTIVE_DUELIST;

  Duel_DrawCards(turnDuelist, 2, TRUE);
}
