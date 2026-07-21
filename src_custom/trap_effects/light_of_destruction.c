#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "light_of_destruction.h"

static u8 sLightOfDestructionReentry APPEND_DATA = {0};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void ActivateLIGHT_OF_DESTRUCTIONZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, LIGHT_OF_DESTRUCTION) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateLIGHT_OF_DESTRUCTIONOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(LIGHT_OF_DESTRUCTION,
                                         ActivateLIGHT_OF_DESTRUCTIONZone);
}

void TryApplyLightOfDestructionAfterMill(u8 milledTurnDuelist, u8 count)
{
  u8 milledFixed;
  u8 controller;

  if (sLightOfDestructionReentry || count == 0 || IsDuelOver() == TRUE)
    return;

  milledFixed = FixedDuelistForTurnDuelist(milledTurnDuelist);
  controller = milledFixed == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  if (Duel_FindBackrowCard(controller, LIGHT_OF_DESTRUCTION, TRUE) == NULL)
    return;

  sLightOfDestructionReentry = TRUE;
  Duel_ShowEffectText(LIGHT_OF_DESTRUCTION);
  Duel_MillTopDeckCards(milledTurnDuelist, 3, TRUE);
  sLightOfDestructionReentry = FALSE;
}
