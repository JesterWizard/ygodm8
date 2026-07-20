#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "spell_effects.h"

#define TRIANGLE_ECSTASY_SPARK_ATK 2700

static u8 IsHarpieLadySisters(u16 cardId)
{
  return cardId == HARPIE_LADY_SISTERS;
}

static void ApplySistersAtkBecomes2700(struct DuelCard *zone)
{
  u16 currentAtk;
  s32 needed;
  s8 delta;

  if (zone == NULL || !IsHarpieLadySisters(zone->id))
    return;

  currentAtk = Duel_GetZoneFinalAtk(zone);
  needed = (s32)TRIANGLE_ECSTASY_SPARK_ATK - (s32)currentAtk;

  /* Round to nearest 500-ATK stage (temp stages clear at EOT). */
  if (needed >= 0)
    delta = (s8)((needed + 250) / 500);
  else
    delta = (s8)((needed - 250) / 500);

  while (delta > 0) {
    IncrementTempStage(zone);
    delta--;
  }
  while (delta < 0) {
    DecrementTempStage(zone);
    delta++;
  }
}

static void BoostAllHarpieLadySisters(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++)
      ApplySistersAtkBecomes2700(gFixedZones[row][col]);
  }
}

static void TRIANGLE_ECSTASY_SPARK_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  BoostAllHarpieLadySisters();

  Duel_ShowEffectText(TRIANGLE_ECSTASY_SPARK);
  RefreshFieldMonsterStatOverlays();

  /* ponytail: stage unit is 500 ATK — Sisters (1950) become 2450 or 2950, not
   * exact printed 2700. Ceiling: nearest-stage temp boost until EOT; upgrade:
   * exact-ATK overlay (like riryoku) forced to 2700 until End Phase clear. */

  /* ponytail: opponent cannot activate Trap Cards / negate opp Trap effects
   * until EOT needs a trap-activation / trap-resolve gate outside this file.
   * Ceiling: Sisters ATK approx only; upgrade: turn flag → block
   * CanActivateTrap / trap effect resolve for INACTIVE_DUELIST until End Phase. */
}

APPEND_TEXT void EffectTRIANGLE_ECSTASY_SPARK(void)
{
  if (Duel_TryResolveSpellThroughTraps(TRIANGLE_ECSTASY_SPARK,
                                       TRIANGLE_ECSTASY_SPARK_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TRIANGLE_ECSTASY_SPARK_SelfCheck(void)
{
  if (!IsHarpieLadySisters(HARPIE_LADY_SISTERS))
    while (1)
      ;
  if (IsHarpieLadySisters(HARPIE_LADY))
    while (1)
      ;
  if (TRIANGLE_ECSTASY_SPARK_ATK != 2700)
    while (1)
      ;
}
#endif
