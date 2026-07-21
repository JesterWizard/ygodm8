#include "global.h"
#include "common-chax.h"
#include "atlantean_attack_squad.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define ATLANTEAN_ATTACK_SQUAD_BASE_ATK 1400
#define ATLANTEAN_ATTACK_SQUAD_ATK_BONUS 800

static u8 IsFishSeaSerpentOrAqua(u16 cardId)
{
  return Duel_CardHasMonsterType(cardId, TYPE_FISH)
      || Duel_CardHasMonsterType(cardId, TYPE_SEA_DRAGON)
      || Duel_CardHasMonsterType(cardId, TYPE_AQUA);
}

static u8 RowHasOtherFaceUpFishSsAqua(u8 fixedRow, const struct DuelCard *self)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == NULL || zone == self || zone->id == CARD_NONE || !zone->isFaceUp)
      continue;
    if (IsFishSeaSerpentOrAqua(zone->id))
      return TRUE;
  }
  return FALSE;
}

u8 AtlanteanAttackSquad_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u16 atk;

  if (zone == NULL || zone->id != ATLANTEAN_ATTACK_SQUAD)
    return FALSE;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  atk = ATLANTEAN_ATTACK_SQUAD_BASE_ATK;
  if (RowHasOtherFaceUpFishSsAqua(fixedRow, zone))
    atk = Duel_ClampStat(ATLANTEAN_ATTACK_SQUAD_BASE_ATK + ATLANTEAN_ATTACK_SQUAD_ATK_BONUS);

  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

unsigned char CanActivateATLANTEAN_ATTACK_SQUAD(void)
{
  if (gMonEffect.id != ATLANTEAN_ATTACK_SQUAD)
    return FALSE;

  /* Continuous ATK via AtlanteanAttackSquad_ApplyDynamicZoneStats. */
  return FALSE;
}

void ActivateATLANTEAN_ATTACK_SQUADEffect(void)
{
  Duel_ShowEffectTextTyped(ATLANTEAN_ATTACK_SQUAD, 2);
}
