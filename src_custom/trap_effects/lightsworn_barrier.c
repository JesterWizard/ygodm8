#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "lightsworn_barrier.h"

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

void LockMonsterCardsInRow(unsigned char turnRow);

static void ActivateLIGHTSWORN_BARRIERZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, LIGHTSWORN_BARRIER) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateLIGHTSWORN_BARRIEROnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(LIGHTSWORN_BARRIER, ActivateLIGHTSWORN_BARRIERZone);
}

void LightswornBarrier_OnAttackDeclare(struct DuelCard *attacker, struct DuelCard *defender)
{
  u8 controller;
  u8 turnDuelist;

  (void)attacker;
  if (defender == NULL || defender->id == CARD_NONE)
    return;
  if (!Duel_CardNameContains(defender->id, sLightswornName))
    return;

  controller = GetDuelistForZone(defender);
  if (controller > DUEL_OPPONENT)
    return;
  if (Duel_FindBackrowCard(controller, LIGHTSWORN_BARRIER, TRUE) == NULL)
    return;

  turnDuelist = (gTurnDuelistBattleState[ACTIVE_DUELIST]
                     == &gDuel.duelistbattleState[controller])
                    ? ACTIVE_DUELIST
                    : INACTIVE_DUELIST;

  Duel_ShowEffectText(LIGHTSWORN_BARRIER);
  Duel_MillTopDeckCards(turnDuelist, 2, TRUE);
  LockMonsterCardsInRow(ACTIVE_DUELIST_MONSTER_ROW);
}
