#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

static u32 SumLevelTwoOrLowerAtkOnRow(u8 turnRow)
{
  u32 sum = 0;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.level == 0 || gCardInfo.level > 2)
      continue;

    sum += Duel_GetZoneFinalAtk(zone);
  }

  return sum;
}

static void ApplyAtkBonusViaTempStage(struct DuelCard *zone, u32 bonusAtk)
{
  u8 stages = (u8)(bonusAtk / 500);

  while (stages--)
    IncrementTempStage(zone);
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
  u32 bonusAtk;

  Duel_ShowEffectTextTyped(JUNK_WARRIOR, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  bonusAtk = SumLevelTwoOrLowerAtkOnRow(gActiveEffect.turnRow);
  ApplyAtkBonusViaTempStage(zone, bonusAtk);
  zone->unk4 = 1;
  RefreshFieldMonsterStatOverlays();
  /* ponytail: tempStage (~500/stage) on-summon only; no continuous recompute. */
}
