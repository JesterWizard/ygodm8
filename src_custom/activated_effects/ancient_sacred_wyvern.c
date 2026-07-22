#include "global.h"
#include "common-chax.h"
#include "ancient_sacred_wyvern.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

u8 GetDuelistForZone(struct DuelCard *zone);

u8 AncientSacredWyvern_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 me;
  u8 opp;
  s32 diff;
  u16 base;
  u16 atk;

  if (zone == NULL || zone->id != ANCIENT_SACRED_WYVERN)
    return FALSE;

  me = GetDuelistForZone(zone);
  if (me > DUEL_OPPONENT)
    return FALSE;

  opp = me == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  diff = (s32)gDuelLifePoints[me] - (s32)gDuelLifePoints[opp];
  if (diff < 0)
    diff = -diff;

  SetCardInfo(zone->id);
  base = gCardInfo.atk;
  if ((s32)gDuelLifePoints[me] >= (s32)gDuelLifePoints[opp])
    atk = Duel_ClampStat((u32)base + (u32)diff);
  else
    atk = (base > (u16)diff) ? (u16)(base - (u16)diff) : 0;

  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

unsigned char CanActivateANCIENT_SACRED_WYVERN(void)
{
  if (gMonEffect.id != ANCIENT_SACRED_WYVERN)
    return FALSE;

  /* Continuous LP→ATK via AncientSacredWyvern_ApplyDynamicZoneStats.
   * ponytail: battle-destroy pay 1000 → SS self need battle/GY hooks. */
  return FALSE;
}

void ActivateANCIENT_SACRED_WYVERNEffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_SACRED_WYVERN, 2);
}
