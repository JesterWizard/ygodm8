#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "harpie_lady_1.h"
#include "configs/runtime.h"

static const char sHarpieArchetypeName[] APPEND_RODATA = "Harpie";

/* Attack-position summons often keep isFaceUp=0 until EOT flip. */
static u8 MonsterCountsAsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 CountHarpieArchetypeOnFixedRowExcluding(u8 fixedRow, u16 excludeId)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *other = gFixedZones[fixedRow][col];

    if (!MonsterCountsAsFaceUp(other))
      continue;
    if (other->id == excludeId)
      continue;
    if (!Duel_CardNameContains(other->id, sHarpieArchetypeName))
      continue;

    count++;
  }

  return count;
}

// +2 other Harpies → double original ATK/DEF
u8 HarpiesPetBabyDragon_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id != HARPIES_PET_BABY_DRAGON)
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  if (CountHarpieArchetypeOnFixedRowExcluding(fixedRow, HARPIES_PET_BABY_DRAGON) < 2)
    return FALSE;

  // Reload after CountHarpieArchetypeOnFixedRowExcluding — Duel_CardNameContains
  // calls SetCardInfo and leaves gCardInfo on the last matching Harpie checked.
  SetCardInfo(zone->id);
  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk * 2);
  gCardInfo.def = Duel_ClampStat((u32)gCardInfo.def * 2);
  ApplyHarpieLady1WindAtkBoost(zone);
  return TRUE;
}

// +1 other Harpie → Pet Baby Dragon cannot be targeted for attacks
u8 HarpiesPetBabyDragon_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id != HARPIES_PET_BABY_DRAGON || !zone->isFaceUp)
    return TRUE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return TRUE;

  if (CountHarpieArchetypeOnFixedRowExcluding(fixedRow, HARPIES_PET_BABY_DRAGON) >= 1)
    return FALSE; // protected by other Harpies

  return TRUE;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HarpiesPetBabyDragon_SelfCheck(void)
{
  struct DuelCard zone;
  zone.id = HARPIES_PET_BABY_DRAGON;
  (void)HarpiesPetBabyDragon_ApplyDynamicZoneStats(&zone);
}
#endif
