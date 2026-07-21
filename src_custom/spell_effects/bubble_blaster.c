#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

/* 1 stage ~= 500 ATK. Printed +800; nearest stage unit is +1000 (2 stages). */
#define BUBBLE_BLASTER_ATK_STAGES 2

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidBubbleBlasterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return zone->id == ELEMENTAL_HERO_BUBBLEMAN;
}

static u8 HasBubbleBlasterTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidBubbleBlasterTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateBUBBLE_BLASTER(void)
{
  return HasBubbleBlasterTarget();
}

static void EquipBubbleBlaster(struct DuelCard *spellZone, struct DuelCard *target)
{
  /* ponytail: stage unit is 500 ATK — applied +1000, not printed +800.
   * Ceiling: no fractional stages; upgrade: exact-ATK overlay like H_HEATED_HEART
   * after listing BUBBLE_BLASTER in IsActiveDynamicEquipSpellZone. */

  ApplyDynamicEquipStages(target, BUBBLE_BLASTER_ATK_STAGES);
  if (!RegisterDynamicEquip(spellZone, target, BUBBLE_BLASTER, BUBBLE_BLASTER_ATK_STAGES))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: battle-destroy this instead + battle damage 0 needs
   * CanMonsterBeDestroyedByBattle / Duel_ApplyBattleDestroyProtection + damage
   * step hook outside this file. Ceiling: Bubbleman equip + ATK only; upgrade:
   * if DynamicEquipTargetsMonsterWithSpell(zone, BUBBLE_BLASTER) would be battle-
   * destroyed → destroy BUBBLE_BLASTER instead and set battle damage to 0. */
}

static void ResolveBubbleBlasterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidBubbleBlasterTarget(fixedRow, fixedCol))
    return;

  EquipBubbleBlaster(spellZone, target);
}

static void CancelBubbleBlasterTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == BUBBLE_BLASTER)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickBubbleBlasterTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidBubbleBlasterTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void BUBBLE_BLASTER_ResolveBody(void)
{
  Duel_ShowEffectText(BUBBLE_BLASTER);

  if (IsDuelOver() == TRUE || !CanActivateBUBBLE_BLASTER())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidBubbleBlasterTarget, ResolveBubbleBlasterTarget,
                     CancelBubbleBlasterTargeting, AiPickBubbleBlasterTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectBUBBLE_BLASTER(void)
{
  if (!CanActivateBUBBLE_BLASTER()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(BUBBLE_BLASTER, BUBBLE_BLASTER_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void BUBBLE_BLASTER_SelfCheck(void)
{
  if (ELEMENTAL_HERO_BUBBLEMAN == CARD_NONE)
    while (1)
      ;
  if (BUBBLE_BLASTER_ATK_STAGES != 2)
    while (1)
      ;
}
#endif
