#include "global.h"
#include "common-chax.h"
#include "arcana_force_coin.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

unsigned char ShouldActivateARCANA_FORCE_VI_THE_LOVERS(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ARCANA_FORCE_VI_THE_LOVERS)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return ArcanaForce_CoinPending(zone);
}

void ActivateARCANA_FORCE_VI_THE_LOVERS(void)
{
  struct DuelCard *zone;
  u8 heads;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_VI_THE_LOVERS, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL || !ArcanaForce_CoinPending(zone))
    return;

  heads = RandRangeU8(0, 1) == 1;
  ArcanaForce_SetCoin(zone, heads);
  /* Printed remainder omitted by this ruleset. */
}
