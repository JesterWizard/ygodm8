#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "shard_of_greed.h"
#include "spell_effects.h"

#define SHARD_OF_GREED_COUNTER_COST 2
#define SHARD_OF_GREED_DRAW_COUNT 2

static u8 CanShardOfGreedIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != SHARD_OF_GREED || zone->isFaceUp == FALSE)
    return FALSE;

  /* unk4 = Greed Counter count (placed by Draw Phase hook when wired). */
  return zone->unk4 >= SHARD_OF_GREED_COUNTER_COST;
}

static void ResolveShardOfGreedIgnition(struct DuelCard *zone)
{
  if (!CanShardOfGreedIgnition(zone))
    return;

  Duel_ShowEffectText(SHARD_OF_GREED);

  if (IsDuelOver() == TRUE)
    return;

  zone->unk4 = 0;
  Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  Duel_DrawCards(ACTIVE_DUELIST, SHARD_OF_GREED_DRAW_COUNT, TRUE);
}

static void SHARD_OF_GREED_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation: send this with 2+ Greed Counters to GY; draw 2. */
  if (zone != NULL && zone->isLocked) {
    if (!CanShardOfGreedIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveShardOfGreedIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  if (zone != NULL)
    zone->unk4 = 0;

  Duel_ShowEffectText(SHARD_OF_GREED);
}

void ShardOfGreed_OnNormalDraw(u8 fixedDuelist)
{
  struct DuelCard *zone;
  u8 col;
  u8 row;

  if (fixedDuelist > DUEL_OPPONENT)
    return;

  row = fixedDuelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gFixedZones[row][col];
    if (zone != NULL && zone->id == SHARD_OF_GREED && zone->isFaceUp && zone->isLocked) {
      if (zone->unk4 < 255)
        zone->unk4++;
    }
  }
}

APPEND_TEXT void EffectSHARD_OF_GREED(void)
{
  if (Duel_TryResolveSpellThroughTraps(SHARD_OF_GREED, SHARD_OF_GREED_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void SHARD_OF_GREED_SelfCheck(void)
{
  if (SHARD_OF_GREED_COUNTER_COST != 2)
    while (1)
      ;
  if (SHARD_OF_GREED_DRAW_COUNT != 2)
    while (1)
      ;
}
#endif
