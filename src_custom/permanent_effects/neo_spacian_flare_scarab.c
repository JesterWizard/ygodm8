#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define NEO_SPACIAN_FLARE_SCARAB_ATK_PER_ST 400

static u8 OpponentBackrowForZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return 0xFF;

  return fixedRow == PLAYER_MONSTER_ROW ? OPPONENT_BACKROW : PLAYER_BACKROW;
}

static u8 CountOpponentSpellTraps(struct DuelCard *zone)
{
  u8 backrow = OpponentBackrowForZone(zone);
  u8 col;
  u8 count = 0;

  if (backrow == 0xFF)
    return 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *slot = gFixedZones[backrow][col];

    if (slot == NULL || slot->id == CARD_NONE)
      continue;
    if (GetTypeGroup(slot->id) == TYPE_GROUP_MONSTER)
      continue;

    count++;
  }

  return count;
}

u8 NeoSpacianFlareScarab_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 baseAtk;
  u32 atk;

  if (zone == NULL || zone->id != NEO_SPACIAN_FLARE_SCARAB)
    return FALSE;

  baseAtk = gCardData_NEW[zone->id].atk;
  atk = (u32)baseAtk + (u32)CountOpponentSpellTraps(zone) * NEO_SPACIAN_FLARE_SCARAB_ATK_PER_ST;
  Duel_WriteCardInfoStats(zone->id, Duel_ClampStat(atk), gCardData_NEW[zone->id].def);
  return TRUE;
}

unsigned char ShouldActivateNEO_SPACIAN_FLARE_SCARAB(void)
{
  /* ponytail: continuous +400 ATK per opp Spell/Trap — ApplyDynamicZoneStats only. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateNEO_SPACIAN_FLARE_SCARAB(void)
{
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void NeoSpacianFlareScarab_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = NEO_SPACIAN_FLARE_SCARAB;
  NeoSpacianFlareScarab_ApplyDynamicZoneStats(&zone);
}
#endif
