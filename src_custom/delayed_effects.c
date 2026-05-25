#include "global.h"
#include "delayed_effects.h"

void ResetDelayedDuelEffects(void)
{
  gDelayedDuelEffects[DUEL_PLAYER] = 0;
  gDelayedDuelEffects[DUEL_OPPONENT] = 0;
}

void QueueDelayedDuelEffect(u8 duelist, u8 effectBit)
{
  gDelayedDuelEffects[duelist] |= effectBit;
}

u8 ConsumeDelayedDuelEffect(u8 duelist, u8 effectBit)
{
  if (!(gDelayedDuelEffects[duelist] & effectBit))
    return FALSE;

  gDelayedDuelEffects[duelist] &= ~effectBit;
  return TRUE;
}

void ResolveDelayedDuelEffectsAtTurnEnd(u8 duelist)
{
  u8 i;

  if (ConsumeDelayedDuelEffect(duelist, DELAYED_DUEL_EFFECT_CARD_OF_DEMISE))
  {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    {
      if (gDuel.hands[duelist][i].id != CARD_NONE)
        ClearZoneAndSendMonToGraveyard(&gDuel.hands[duelist][i], duelist);
    }
  }
}
