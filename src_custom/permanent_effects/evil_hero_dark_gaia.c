#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "evil_hero_dark_gaia.h"

#define DARK_GAIA_CELL_NONE 0xFF

static u8 FixedMonsterCellIndex(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return (MAX_ZONES_IN_ROW - 1) - fixedCol;
  if (fixedRow == PLAYER_MONSTER_ROW)
    return MAX_ZONES_IN_ROW + fixedCol;
  return DARK_GAIA_CELL_NONE;
}

static u8 GetFixedCellIndexForZone(struct DuelCard *zone, u8 *cellIndex)
{
  u8 fixedRow;
  u8 fixedCol;

  if (Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol) == FALSE)
    return FALSE;

  *cellIndex = FixedMonsterCellIndex(fixedRow, fixedCol);
  return *cellIndex != DARK_GAIA_CELL_NONE;
}

void EvilHeroDarkGaia_StampFusionMaterialAtk(u16 atkSum)
{
  u8 col;
  struct DuelCard *zone = NULL;
  u8 cellIndex;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    if (zone != NULL && zone->id == EVIL_HERO_DARK_GAIA) {
      if (GetFixedCellIndexForZone(zone, &cellIndex))
        gEvilHeroDarkGaiaFusionAtk[cellIndex] = atkSum;
      return;
    }
  }
}

u8 EvilHeroDarkGaia_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 cellIndex;
  u16 atk;

  if (zone == NULL || zone->id != EVIL_HERO_DARK_GAIA)
    return FALSE;

  if (!GetFixedCellIndexForZone(zone, &cellIndex))
    return FALSE;

  atk = gEvilHeroDarkGaiaFusionAtk[cellIndex];
  if (atk == 0)
    atk = gCardData_NEW[zone->id].atk;

  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

void EvilHeroDarkGaia_ClearBoardStatsForZone(struct DuelCard *zone)
{
  u8 cellIndex;

  if (!GetFixedCellIndexForZone(zone, &cellIndex))
    return;

  gEvilHeroDarkGaiaFusionAtk[cellIndex] = 0;
}

unsigned char ShouldActivateEVIL_HERO_DARK_GAIA(void)
{
  /* Fusion ATK via EvilHeroDarkGaia_ApplyDynamicZoneStats + fusion stamp.
   * Ceiling: flip opp Defense→Attack needs battle hook. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_DARK_GAIA(void)
{
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void EvilHeroDarkGaia_SelfCheck(void)
{
  struct DuelCard zone;

  gEvilHeroDarkGaiaFusionAtk[0] = 3500;
  zone.id = EVIL_HERO_DARK_GAIA;
  SetCardInfo(zone.id);
  EvilHeroDarkGaia_ApplyDynamicZoneStats(&zone);
  if (gCardInfo.atk != 3500)
    while (1)
      ;
}
#endif
