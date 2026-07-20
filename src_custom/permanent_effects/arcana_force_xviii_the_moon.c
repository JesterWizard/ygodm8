#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define ARCANA_FORCE_XVIII_THE_MOON_COIN_HEADS 1
#define ARCANA_FORCE_XVIII_THE_MOON_COIN_TAILS 2

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

unsigned char ShouldActivateARCANA_FORCE_XVIII_THE_MOON(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ARCANA_FORCE_XVIII_THE_MOON)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return TRUE;
}

void ActivateARCANA_FORCE_XVIII_THE_MOON(void)
{
  struct DuelCard *zone;
  u8 heads;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XVIII_THE_MOON, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  heads = RandRangeU8(0, 1) == 1;
  zone->unk4 = heads ? ARCANA_FORCE_XVIII_THE_MOON_COIN_HEADS
                     : ARCANA_FORCE_XVIII_THE_MOON_COIN_TAILS;
  /* ponytail: Standby Moon Token / End Phase give-control need turn hooks; unk4 only. */
}
