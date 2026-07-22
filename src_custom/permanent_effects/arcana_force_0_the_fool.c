#include "global.h"
#include "common-chax.h"
#include "arcana_force_0_the_fool.h"
#include "arcana_force_coin.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

u8 ArcanaForce0TheFool_PreventsBattleDestroy(const struct DuelCard *zone)
{
  /* Heads: cannot be destroyed by battle. */
  return zone != NULL && zone->id == ARCANA_FORCE_0_THE_FOOL
      && zone->unk4 == ARCANA_FORCE_COIN_HEADS;
}

unsigned char ShouldActivateARCANA_FORCE_0_THE_FOOL(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ARCANA_FORCE_0_THE_FOOL)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  return ArcanaForce_CoinPending(zone);
}

void ActivateARCANA_FORCE_0_THE_FOOL(void)
{
  struct DuelCard *zone;
  u8 heads;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_0_THE_FOOL, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL || !ArcanaForce_CoinPending(zone))
    return;

  heads = RandRangeU8(0, 1) == 1;
  ArcanaForce_SetCoin(zone, heads);
  /* Printed remainder omitted by this ruleset. */
}
