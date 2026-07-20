#include "global.h"
#include "common-chax.h"
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

unsigned char CanActivateGOLDEN_HOMUNCULUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GOLDEN_HOMUNCULUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GOLDEN_HOMUNCULUS)
    return FALSE;

  /* Allow one refresh while unused this turn (stand-in for continuous overlay). */
  return CanUseMonsterEffect(zone);
}

void ActivateGOLDEN_HOMUNCULUSEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForMonEffect();
  u8 banished = 0;
  u8 stages;
  u8 i;

  Duel_ShowEffectTextTyped(GOLDEN_HOMUNCULUS, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  /* ponytail: continuous +300 ATK/DEF per banished needs permanent stat overlay.
   * Ceiling: OPT refresh sets perm stages ≈ banished*300/500. */

  if (RemovedFromPlay_IsEnabled())
    banished = RemovedFromPlay_GetCount(fixedDuelist);

  stages = (u8)((banished * 300) / 500);
  if (stages > 10)
    stages = 10;

  SetPermStage(zone, stages);
  MarkMonsterEffectUsed(zone);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
