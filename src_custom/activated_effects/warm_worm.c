#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "warm_worm.h"

static u8 sWarmWormInit APPEND_DATA = {0};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static void TryWarmWormMill(u8 ownerFixed)
{
  u8 ownerTurn = TurnDuelistForFixed(ownerFixed);
  u8 oppTurn = ownerTurn == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  Duel_ShowEffectTextTyped(WARM_WORM, 2);
  Duel_MillTopDeckCards(oppTurn, 3, TRUE);
}

static void OnWarmWormDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != WARM_WORM)
    return;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  TryWarmWormMill(ev->controller);
}

void WarmWorm_EnsureInit(void)
{
  if (sWarmWormInit)
    return;
  sWarmWormInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnWarmWormDestroyed);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnWarmWormDestroyed);
}

unsigned char CanActivateWARM_WORM(void)
{
  if (gMonEffect.id != WARM_WORM)
    return FALSE;

  /* Destroy mill via WarmWorm_EnsureInit. */
  return FALSE;
}

void ActivateWARM_WORMEffect(void)
{
  Duel_ShowEffectTextTyped(WARM_WORM, 2);
}
