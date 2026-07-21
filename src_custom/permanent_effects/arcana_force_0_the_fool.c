#include "global.h"
#include "common-chax.h"
#include "arcana_force_0_the_fool.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define ARCANA_FORCE_0_THE_FOOL_COIN_HEADS 1
#define ARCANA_FORCE_0_THE_FOOL_COIN_TAILS 2

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

u8 ArcanaForce0TheFool_PreventsBattleDestroy(const struct DuelCard *zone)
{
  /* Heads: cannot be destroyed by battle. */
  return zone != NULL && zone->id == ARCANA_FORCE_0_THE_FOOL
      && zone->unk4 == ARCANA_FORCE_0_THE_FOOL_COIN_HEADS;
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
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return TRUE;
}

void ActivateARCANA_FORCE_0_THE_FOOL(void)
{
  struct DuelCard *zone;
  u8 heads;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_0_THE_FOOL, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  heads = RandRangeU8(0, 1) == 1;
  zone->unk4 = heads ? ARCANA_FORCE_0_THE_FOOL_COIN_HEADS
                     : ARCANA_FORCE_0_THE_FOOL_COIN_TAILS;
  /* Tails targeting immunity still needs target-hook; Heads battle protect is live. */
}
