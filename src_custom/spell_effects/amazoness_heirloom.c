#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidAmazonessHeirloomTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return Duel_IsAmazonessCard(zone->id);
}

static u8 HasAmazonessHeirloomTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidAmazonessHeirloomTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateAMAZONESS_HEIRLOOM(void)
{
  return HasAmazonessHeirloomTarget();
}

static void EquipAmazonessHeirloom(struct DuelCard *spellZone, struct DuelCard *target)
{
  if (!RegisterDynamicEquip(spellZone, target, AMAZONESS_HEIRLOOM, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone
   * instead of vanilla equip targeting; link cleanup may not treat this as active
   * equip. Ceiling: add AMAZONESS_HEIRLOOM to card_hooks GetSpellType EQUIP list and
   * dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART. */

  /* ponytail: once-per-turn battle-destroy protection needs CanMonsterBeDestroyedByBattle
   * / Duel_ApplyBattleDestroyProtection to check DynamicEquipTargetsMonsterWithSpell
   * (zone, AMAZONESS_HEIRLOOM) + OPT bit. Ceiling: equip-only; upgrade: battle-protect
   * flag cleared EOT / after one save. */

  /* ponytail: after damage calc, if equipped attacks a monster → destroy defender
   * needs a battle_effects post-damage hook outside this file. Ceiling: equip-only;
   * upgrade: after damage calc → if DynamicEquipTargetsMonsterWithSpell(attacker,
   * AMAZONESS_HEIRLOOM) then Duel_DestroyZone(defender). */
}

static void ResolveAmazonessHeirloomTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidAmazonessHeirloomTarget(fixedRow, fixedCol))
    return;

  EquipAmazonessHeirloom(spellZone, target);
}

static void CancelAmazonessHeirloomTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == AMAZONESS_HEIRLOOM)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickAmazonessHeirloomTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidAmazonessHeirloomTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void AMAZONESS_HEIRLOOM_ResolveBody(void)
{
  Duel_ShowEffectText(AMAZONESS_HEIRLOOM);

  if (IsDuelOver() == TRUE || !CanActivateAMAZONESS_HEIRLOOM())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidAmazonessHeirloomTarget, ResolveAmazonessHeirloomTarget,
                     CancelAmazonessHeirloomTargeting, AiPickAmazonessHeirloomTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectAMAZONESS_HEIRLOOM(void)
{
  if (!CanActivateAMAZONESS_HEIRLOOM()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(AMAZONESS_HEIRLOOM, AMAZONESS_HEIRLOOM_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void AMAZONESS_HEIRLOOM_SelfCheck(void)
{
  if (!Duel_IsAmazonessCard(AMAZONESS_QUEEN))
    while (1)
      ;
  if (Duel_IsAmazonessCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
