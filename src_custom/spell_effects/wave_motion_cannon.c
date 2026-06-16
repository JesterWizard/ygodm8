#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "spell_effects.h"
#include "wave_motion_cannon.h"

#define WAVE_MOTION_CANNON_DAMAGE_PER_TURN 1000

static u16 GetWaveMotionCannonDamage(const struct DuelCard *zone)
{
  u8 turns = zone->permStage;
  u32 damage = (u32)turns * WAVE_MOTION_CANNON_DAMAGE_PER_TURN;

  if (damage > 65535)
    damage = 65535;

  return (u16)damage;
}

static void PlaceWaveMotionCannon(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ResetPermStage(zone);
  Duel_ShowEffectText(WAVE_MOTION_CANNON);
}

static void WaveMotionCannon_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u16 damage = GetWaveMotionCannonDamage(zone);

  if (damage != 0
      && Duel_ChangeLp(INACTIVE_DUELIST, -(s32)damage, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(zone, ACTIVE_DUELIST, TRUE);
}

static void FireWaveMotionCannon(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(WAVE_MOTION_CANNON, GetWaveMotionCannonDamage(
                                           gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]),
                                         WaveMotionCannon_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

APPEND_TEXT void EffectWaveMotionCannon(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (IsChargedWaveMotionCannon(zone))
    FireWaveMotionCannon();
  else
    PlaceWaveMotionCannon();
}
