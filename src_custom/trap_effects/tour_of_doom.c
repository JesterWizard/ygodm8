#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "tour_of_doom.h"

static u8 sTourOfDoomPendingBlockFixed APPEND_DATA = {0xFF};

static void ActivateTOUR_OF_DOOMZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, TOUR_OF_DOOM) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateTOUR_OF_DOOMOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(TOUR_OF_DOOM, ActivateTOUR_OF_DOOMZone);
}

void TryApplyTourOfDoomStandby(void)
{
  u8 col;
  struct DuelCard *zone;
  u8 heads;
  u8 activeFixed;

  if (IsDuelOver() == TRUE)
    return;

  /* Pending coin result: block NS/Flip for that controller's turn. */
  if (sTourOfDoomPendingBlockFixed == WhoseTurn()) {
    gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked = 1;
    sTourOfDoomPendingBlockFixed = 0xFF;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];
    if (zone == NULL || zone->id != TOUR_OF_DOOM || zone->isFaceUp == FALSE)
      continue;

    heads = RandRangeU8(0, 1) == 1;
    activeFixed = WhoseTurn();
    Duel_ShowEffectText(TOUR_OF_DOOM);

    if (heads) {
      /* Opp cannot NS/Flip until their EP → block on their next Standby. */
      sTourOfDoomPendingBlockFixed =
          activeFixed == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
    } else {
      /* You cannot next turn. */
      sTourOfDoomPendingBlockFixed = activeFixed;
    }
    return;
  }
}
