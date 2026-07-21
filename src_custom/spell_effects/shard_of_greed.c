#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
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

  /* ponytail: Greed Counters on normal Draw Phase draw need a draw-phase hook
   * outside this file (no in-file normal-draw dispatch).
   * Ceiling: continuous face-up + ignition when unk4>=2 (never rises alone);
   * upgrade: Draw Phase normal-draw listener → if face-up SHARD_OF_GREED then
   * zone->unk4++ (cap optional). */
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
