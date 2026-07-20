#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

/* 1 stage ~= 500 ATK. Printed +500. */
#define CELESTIAL_SWORD_EATOS_ATK_STAGES 1
#define CELESTIAL_SWORD_EATOS_GY_ATK_PER_BANISH_STAGES 1

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidCelestialSwordTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return Duel_SpellMayTargetMonsterZone(zone);
}

static u8 HasCelestialSwordTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidCelestialSwordTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateCELESTIAL_SWORD_EATOS(void)
{
  return HasCelestialSwordTarget();
}

static void EquipCelestialSword(struct DuelCard *spellZone, struct DuelCard *target)
{
  ApplyDynamicEquipStages(target, CELESTIAL_SWORD_EATOS_ATK_STAGES);
  if (!RegisterDynamicEquip(spellZone, target, CELESTIAL_SWORD_EATOS,
                            CELESTIAL_SWORD_EATOS_ATK_STAGES))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: always treated as a Noble Arms card needs a name/archetype tag
   * outside this file. Ceiling: equip +ATK only; upgrade: treat-as / name contains
   * "Noble Arms" for Noble Arms support. */

  /* ponytail: send-from-field-to-GY → target Guardian Eatos for +500 ATK per
   * banished monster needs a leave-field / destroy hook outside this file
   * (OnDynamicEquipZoneAboutToClear). Ceiling: equip +500 only; upgrade: leave-
   * hook → PickZone GUARDIAN_EATOS then ApplyDynamicEquipStages /
   * IncrementTempStage × banished count (CELESTIAL_SWORD_EATOS_GY_ATK_PER_BANISH_STAGES). */

  /* ponytail: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone
   * instead of vanilla equip targeting; link cleanup may not treat this as active
   * equip. Ceiling: add CELESTIAL_SWORD_EATOS to card_hooks GetSpellType EQUIP list
   * and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as
   * H_HEATED_HEART. */

  (void)CELESTIAL_SWORD_EATOS_GY_ATK_PER_BANISH_STAGES;
}

static void ResolveCelestialSwordTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidCelestialSwordTarget(fixedRow, fixedCol))
    return;

  EquipCelestialSword(spellZone, target);
}

static void CancelCelestialSwordTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == CELESTIAL_SWORD_EATOS)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickCelestialSwordTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidCelestialSwordTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void CELESTIAL_SWORD_EATOS_ResolveBody(void)
{
  Duel_ShowEffectText(CELESTIAL_SWORD_EATOS);

  if (IsDuelOver() == TRUE || !CanActivateCELESTIAL_SWORD_EATOS())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidCelestialSwordTarget, ResolveCelestialSwordTarget,
                     CancelCelestialSwordTargeting, AiPickCelestialSwordTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectCELESTIAL_SWORD_EATOS(void)
{
  if (!CanActivateCELESTIAL_SWORD_EATOS()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(CELESTIAL_SWORD_EATOS, CELESTIAL_SWORD_EATOS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CELESTIAL_SWORD_EATOS_SelfCheck(void)
{
  if (CELESTIAL_SWORD_EATOS_ATK_STAGES != 1)
    while (1)
      ;
  if (GUARDIAN_EATOS == CARD_NONE)
    while (1)
      ;
}
#endif
