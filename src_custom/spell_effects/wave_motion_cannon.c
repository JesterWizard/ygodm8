#include "global.h"
#include "common-chax.h"
#include "spell_effects.h"
#include "wave_motion_cannon.h"

#define WAVE_MOTION_CANNON_DAMAGE_PER_TURN 1000

extern void ActivateTrapEffect(u16 lp);

static u16 GetWaveMotionCannonDamage(const struct DuelCard *zone)
{
  u8 turns = zone->permStage;
  u32 damage = (u32)turns * WAVE_MOTION_CANNON_DAMAGE_PER_TURN;

  if (damage > 65535)
    damage = 65535;

  return (u16)damage;
}

static void ApplyWaveMotionCannonDamage(u16 damage)
{
  if (damage == 0)
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    SetOpponentLifePointsToSubtract(damage);
  else
    SetPlayerLifePointsToSubtract(damage);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
}

static void PlaceWaveMotionCannon(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ResetPermStage(zone);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = WAVE_MOTION_CANNON;
    ActivateCardEffectText();
  }
}

static void FireWaveMotionCannon(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u16 damage = GetWaveMotionCannonDamage(zone);

  gTrapEffectData.originRow = gSpellEffectData.row1;
  gTrapEffectData.originCol = gSpellEffectData.col1;
  gTrapEffectData.originCardId = WAVE_MOTION_CANNON;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    ApplyWaveMotionCannonDamage(damage);
    ClearZoneAndSendMonToGraveyard(zone, ACTIVE_DUELIST);
  } else {
    ActivateTrapEffect(damage);
  }

  gTrapEffectData.originRow = 0;
  gTrapEffectData.originCol = 0;
}

APPEND_TEXT void EffectWaveMotionCannon(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (IsChargedWaveMotionCannon(zone))
    FireWaveMotionCannon();
  else
    PlaceWaveMotionCannon();
}
