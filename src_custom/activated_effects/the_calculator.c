#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

static u8 SumFaceUpLevelsOnRow(u8 row)
{
  u8 col;
  u8 total = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;
    SetCardInfo(zone->id);
    total += gCardInfo.level;
  }

  return total;
}

unsigned char CanActivateTHE_CALCULATOR(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THE_CALCULATOR)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THE_CALCULATOR)
    return FALSE;

  /* ponytail: continuous ATK = levels×300 needs permanent overlay.
   * Ceiling: OPT refresh perm stages ≈ (levels×300)/500. */
  return CanUseMonsterEffect(zone);
}

void ActivateTHE_CALCULATOREffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 levels;
  u8 stages;

  Duel_ShowEffectTextTyped(THE_CALCULATOR, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  levels = SumFaceUpLevelsOnRow(gMonEffect.row);
  stages = (u8)((levels * 300) / 500);
  if (stages > 20)
    stages = 20;

  SetPermStage(zone, stages);
  MarkMonsterEffectUsed(zone);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
