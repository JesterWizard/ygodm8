#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

static u8 FixedDuelistForMonEffect(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CountOwnBanishedDinosaurs(void)
{
  u8 fixedDuelist = FixedDuelistForMonEffect();
  u8 count = 0;
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return 0;

  for (i = 0; i < RemovedFromPlay_GetCount(fixedDuelist); i++) {
    u16 id = RemovedFromPlay_GetCardAt(fixedDuelist, i);

    if (GetTypeGroup(id) != TYPE_GROUP_MONSTER)
      continue;
    if (Duel_CardHasMonsterType(id, TYPE_DINOSAUR))
      count++;
  }

  return count;
}

unsigned char CanActivateTYRANNO_INFINITY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != TYRANNO_INFINITY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != TYRANNO_INFINITY)
    return FALSE;

  /* ponytail: original ATK = banished Dinos×1000 needs permanent overlay.
   * Ceiling: OPT stages ≈ (count×1000)/500. */
  return CanUseMonsterEffect(zone);
}

void ActivateTYRANNO_INFINITYEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 count;
  u8 stages;

  Duel_ShowEffectTextTyped(TYRANNO_INFINITY, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  count = CountOwnBanishedDinosaurs();
  stages = (u8)((count * 1000) / 500);
  if (stages > 20)
    stages = 20;

  SetPermStage(zone, stages);
  MarkMonsterEffectUsed(zone);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
