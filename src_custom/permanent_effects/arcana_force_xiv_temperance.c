#include "global.h"
#include "common-chax.h"
#include "arcana_force_xiv_temperance.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define ARCANA_FORCE_XIV_TEMPERANCE_COIN_HEADS 1
#define ARCANA_FORCE_XIV_TEMPERANCE_COIN_TAILS 2

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

static u8 ControllerHasTemperanceResult(u8 controller, u8 coinResult)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == ARCANA_FORCE_XIV_TEMPERANCE
        && zone->unk4 == coinResult)
      return TRUE;
  }

  return FALSE;
}

u8 ArcanaForceXivTemperance_ShouldBlockBattleDamage(u8 damagedFixedDuelist)
{
  if (damagedFixedDuelist > DUEL_OPPONENT)
    return FALSE;

  /* Heads: you take no battle damage. Tails: opponent takes none. */
  if (ControllerHasTemperanceResult(damagedFixedDuelist,
                                    ARCANA_FORCE_XIV_TEMPERANCE_COIN_HEADS))
    return TRUE;

  if (ControllerHasTemperanceResult(
          damagedFixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER,
          ARCANA_FORCE_XIV_TEMPERANCE_COIN_TAILS))
    return TRUE;

  return FALSE;
}

unsigned char ShouldActivateARCANA_FORCE_XIV_TEMPERANCE(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ARCANA_FORCE_XIV_TEMPERANCE)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return TRUE;
}

void ActivateARCANA_FORCE_XIV_TEMPERANCE(void)
{
  struct DuelCard *zone;
  u8 heads;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XIV_TEMPERANCE, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  heads = RandRangeU8(0, 1) == 1;
  zone->unk4 = heads ? ARCANA_FORCE_XIV_TEMPERANCE_COIN_HEADS
                     : ARCANA_FORCE_XIV_TEMPERANCE_COIN_TAILS;
}
