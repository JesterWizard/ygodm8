#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "serpent_suppression.h"

void ApplyFieldZoneStatsToCardInfo(struct DuelCard *zone);

static const char sReptilianneName[] APPEND_RODATA = "Reptilianne";

static void ActivateSERPENT_SUPPRESSIONZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, SERPENT_SUPPRESSION)
      == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateSERPENT_SUPPRESSIONOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(SERPENT_SUPPRESSION,
                                         ActivateSERPENT_SUPPRESSIONZone);
}

u8 SerpentSuppression_PreventsBattleDestruction(const struct DuelCard *defender,
                                                 const struct DuelCard *attacker)
{
  u8 controller;
  u16 atk;

  if (defender == NULL || attacker == NULL)
    return FALSE;
  if (defender->isDefending)
    return FALSE;
  if (!Duel_CardNameContains(attacker->id, sReptilianneName))
    return FALSE;

  controller = GetDuelistForZone((struct DuelCard *)attacker);
  if (controller > DUEL_OPPONENT)
    return FALSE;
  if (Duel_FindBackrowCard(controller, SERPENT_SUPPRESSION, TRUE) == NULL)
    return FALSE;

  ApplyFieldZoneStatsToCardInfo((struct DuelCard *)defender);
  atk = gCardInfo.atk;
  return atk == 0;
}
