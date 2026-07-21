#include "global.h"
#include "common-chax.h"
#include "boot_up_soldier_dread_dynamo.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define BOOT_UP_SOLDIER_BASE_ATK 0
#define BOOT_UP_SOLDIER_GADGET_BONUS 2000

static const char sGadgetName[] APPEND_RODATA = "Gadget";

static u8 RowHasGadget(u8 fixedRow, const struct DuelCard *self)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == NULL || zone == self || zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;
    if (Duel_CardNameContains(zone->id, sGadgetName))
      return TRUE;
  }
  return FALSE;
}

u8 BootUpSoldierDreadDynamo_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u16 atk;

  if (zone == NULL || zone->id != BOOT_UP_SOLDIER_DREAD_DYNAMO)
    return FALSE;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  atk = BOOT_UP_SOLDIER_BASE_ATK;
  if (RowHasGadget(fixedRow, zone))
    atk = Duel_ClampStat(BOOT_UP_SOLDIER_BASE_ATK + BOOT_UP_SOLDIER_GADGET_BONUS);

  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

unsigned char CanActivateBOOT_UP_SOLDIER_DREAD_DYNAMO(void)
{
  if (gMonEffect.id != BOOT_UP_SOLDIER_DREAD_DYNAMO)
    return FALSE;

  /* Continuous ATK via BootUpSoldierDreadDynamo_ApplyDynamicZoneStats. */
  return FALSE;
}

void ActivateBOOT_UP_SOLDIER_DREAD_DYNAMOEffect(void)
{
  Duel_ShowEffectTextTyped(BOOT_UP_SOLDIER_DREAD_DYNAMO, 2);
}
