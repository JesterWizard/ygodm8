#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

/* 1 stage ~= 500 ATK. Printed +600; nearest stage unit is +500 (1 stage). */
#define ANCIENT_GEAR_TANK_ATK_STAGES 1
#define ANCIENT_GEAR_TANK_DESTROY_BURN 600

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsAncientGearMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u8 IsValidAncientGearTankTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsAncientGearMonster(zone->id);
}

static u8 HasAncientGearTankTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidAncientGearTankTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateANCIENT_GEAR_TANK(void)
{
  return HasAncientGearTankTarget();
}

static void EquipAncientGearTank(struct DuelCard *spellZone, struct DuelCard *target)
{
  /* ponytail: stage unit is 500 ATK — applied +500, not printed +600.
   * Ceiling: no fractional stages; upgrade: exact-ATK overlay like BIG_BANG_SHOT
   * after listing ANCIENT_GEAR_TANK in IsActiveDynamicEquipSpellZone. */

  ApplyDynamicEquipStages(target, ANCIENT_GEAR_TANK_ATK_STAGES);
  if (!RegisterDynamicEquip(spellZone, target, ANCIENT_GEAR_TANK,
                            ANCIENT_GEAR_TANK_ATK_STAGES))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: destroy→GY burn 600 to opponent needs a field/destroy hook
   * outside this file (OnDynamicEquipZoneAboutToClear / GY send).
   * Ceiling: equip-only works; destroy-burn not wired from this file.
   * Upgrade: destroy-hook → Duel_ChangeLp(INACTIVE_DUELIST,
   * -ANCIENT_GEAR_TANK_DESTROY_BURN). */

  /* ponytail: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone
   * instead of vanilla equip targeting; link cleanup may not treat this as active
   * equip. Ceiling: add ANCIENT_GEAR_TANK to card_hooks GetSpellType EQUIP list and
   * dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART. */

  (void)ANCIENT_GEAR_TANK_DESTROY_BURN;
}

static void ResolveAncientGearTankTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidAncientGearTankTarget(fixedRow, fixedCol))
    return;

  EquipAncientGearTank(spellZone, target);
}

static void CancelAncientGearTankTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == ANCIENT_GEAR_TANK)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickAncientGearTankTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidAncientGearTankTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ANCIENT_GEAR_TANK_ResolveBody(void)
{
  Duel_ShowEffectText(ANCIENT_GEAR_TANK);

  if (IsDuelOver() == TRUE || !CanActivateANCIENT_GEAR_TANK())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidAncientGearTankTarget, ResolveAncientGearTankTarget,
                     CancelAncientGearTankTargeting, AiPickAncientGearTankTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectANCIENT_GEAR_TANK(void)
{
  if (!CanActivateANCIENT_GEAR_TANK()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(ANCIENT_GEAR_TANK, ANCIENT_GEAR_TANK_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ANCIENT_GEAR_TANK_SelfCheck(void)
{
  if (!IsAncientGearMonster(ANCIENT_GEAR_GOLEM))
    while (1)
      ;
  if (IsAncientGearMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (ANCIENT_GEAR_TANK_DESTROY_BURN != 600)
    while (1)
      ;
}
#endif
