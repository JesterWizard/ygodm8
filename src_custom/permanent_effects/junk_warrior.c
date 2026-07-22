#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "junk_warrior.h"

static u32 SumLevelTwoOrLowerAtkOnFixedRow(u8 fixedRow, u8 skipCol)
{
  u32 sum = 0;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (col == skipCol || zone == NULL || zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.level == 0 || gCardInfo.level > 2)
      continue;

    sum += Duel_GetZoneFinalAtk(zone);
  }

  return sum;
}

void ApplyJunkWarriorContinuousAtkToCardInfo(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || zone->id != JUNK_WARRIOR)
    return;

  if (gCardInfo.id != zone->id || gCardInfo.type >= TYPE_SPELL)
    return;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &fixedCol))
    return;

  gCardInfo.atk = (u16)(gCardInfo.atk + SumLevelTwoOrLowerAtkOnFixedRow(fixedRow, fixedCol));
}

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

unsigned char ShouldActivateJUNK_WARRIOR(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != JUNK_WARRIOR)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return TRUE;
}

void ActivateJUNK_WARRIOR(void)
{
  struct DuelCard *zone;

  Duel_ShowEffectTextTyped(JUNK_WARRIOR, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  zone->unk4 = 1;
  RefreshFieldMonsterStatOverlays();
}
