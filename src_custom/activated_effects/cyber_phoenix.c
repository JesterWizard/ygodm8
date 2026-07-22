#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "cyber_phoenix.h"
#include "effect_events.h"

static u8 sCyberPhoenixInit APPEND_DATA = {0};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static void OnCyberPhoenixBattleDestroyed(const struct EffectEvent *ev)
{
  u8 turnDuelist;

  if (ev == NULL || ev->cardId != CYBER_PHOENIX)
    return;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  turnDuelist = TurnDuelistForFixed(ev->controller);
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  Duel_ShowEffectTextTyped(CYBER_PHOENIX, 2);
  Duel_DrawCards(turnDuelist, 1, TRUE);
}

void CyberPhoenix_EnsureInit(void)
{
  if (sCyberPhoenixInit)
    return;
  sCyberPhoenixInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnCyberPhoenixBattleDestroyed);
}

unsigned char CanActivateCYBER_PHOENIX(void)
{
  if (gMonEffect.id != CYBER_PHOENIX)
    return FALSE;

  /* Battle-destroy draw via CyberPhoenix_EnsureInit.
   * ponytail: ATK-position Machine S/T target-negate needs targeting gate. */
  return FALSE;
}

void ActivateCYBER_PHOENIXEffect(void)
{
  Duel_ShowEffectTextTyped(CYBER_PHOENIX, 2);
}
