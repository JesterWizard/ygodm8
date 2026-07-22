#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "morphtronic_videon.h"

#define VIDEON_STAT_PER_EQUIP 800

static u8 CountEquipsOnTarget(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 i;
  u8 count = 0;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col))
    return 0;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    if (gDynamicEquipLinks[i].active
        && gDynamicEquipLinks[i].targetFixedRow == fixedRow
        && gDynamicEquipLinks[i].targetFixedCol == col)
      count++;
  }
  return count;
}

u8 MorphtronicVideon_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 equips;
  u16 atk;
  u16 def;

  if (zone == NULL || zone->id != MORPHTRONIC_VIDEON)
    return FALSE;

  equips = CountEquipsOnTarget(zone);
  SetCardInfo(zone->id);
  atk = gCardInfo.atk;
  def = gCardInfo.def;

  if (zone->isDefending)
    def = Duel_ClampStat((u32)def + (u32)equips * VIDEON_STAT_PER_EQUIP);
  else
    atk = Duel_ClampStat((u32)atk + (u32)equips * VIDEON_STAT_PER_EQUIP);

  Duel_WriteCardInfoStats(zone->id, atk, def);
  return TRUE;
}

unsigned char CanActivateMORPHTRONIC_VIDEON(void)
{
  if (gMonEffect.id != MORPHTRONIC_VIDEON)
    return FALSE;

  /* Continuous equip ATK/DEF via MorphtronicVideon_ApplyDynamicZoneStats. */
  return FALSE;
}

void ActivateMORPHTRONIC_VIDEONEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_VIDEON, 2);
}
