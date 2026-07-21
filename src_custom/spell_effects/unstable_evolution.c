#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"
#include "unstable_evolution.h"

#define UNSTABLE_EVOLUTION_ATK_LOW_LP 2400
#define UNSTABLE_EVOLUTION_ATK_HIGH_LP 1000

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u16 ControllerLifePoints(u8 fixedDuelist)
{
  return gDuelLifePoints[fixedDuelist];
}

static u16 OpponentLifePoints(u8 fixedDuelist)
{
  return gDuelLifePoints[fixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER];
}

static u8 IsValidUnstableEvolutionTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return Duel_SpellMayTargetMonsterZone(zone);
}

static u8 HasUnstableEvolutionTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidUnstableEvolutionTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateUNSTABLE_EVOLUTION(void)
{
  return HasUnstableEvolutionTarget();
}

static u16 DesiredOriginalAtk(u8 controllerFixed)
{
  u16 myLp = ControllerLifePoints(controllerFixed);
  u16 oppLp = OpponentLifePoints(controllerFixed);

  if (myLp < oppLp)
    return UNSTABLE_EVOLUTION_ATK_LOW_LP;
  if (myLp > oppLp)
    return UNSTABLE_EVOLUTION_ATK_HIGH_LP;
  return 0xFFFF; /* equal LP — leave printed ATK */
}

void ApplyUnstableEvolutionAtkToCardInfo(const struct DuelCard *zone)
{
  u8 controller;
  u16 desired;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!DynamicEquipTargetsMonsterWithSpell(zone, UNSTABLE_EVOLUTION))
    return;

  controller = GetDuelistForZone(zone);
  if (controller != DUEL_PLAYER && controller != DUEL_OPPONENT)
    return;

  desired = DesiredOriginalAtk(controller);
  if (desired == 0xFFFF)
    return;

  gCardInfo.atk = desired;
}

static void EquipUnstableEvolution(struct DuelCard *spellZone, struct DuelCard *target)
{
  if (!RegisterDynamicEquip(spellZone, target, UNSTABLE_EVOLUTION, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
  Duel_NotifyMonsterZoneChanged(target);
  Duel_RefreshMonsterStatOverlays();
}

static void ResolveUnstableEvolutionTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidUnstableEvolutionTarget(fixedRow, fixedCol))
    return;

  EquipUnstableEvolution(spellZone, target);
}

static void CancelUnstableEvolutionTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == UNSTABLE_EVOLUTION)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickUnstableEvolutionTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidUnstableEvolutionTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void UNSTABLE_EVOLUTION_ResolveBody(void)
{
  Duel_ShowEffectText(UNSTABLE_EVOLUTION);

  if (IsDuelOver() == TRUE || !CanActivateUNSTABLE_EVOLUTION())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidUnstableEvolutionTarget, ResolveUnstableEvolutionTarget,
                     CancelUnstableEvolutionTargeting, AiPickUnstableEvolutionTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectUNSTABLE_EVOLUTION(void)
{
  if (!CanActivateUNSTABLE_EVOLUTION()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(UNSTABLE_EVOLUTION, UNSTABLE_EVOLUTION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void UNSTABLE_EVOLUTION_SelfCheck(void)
{
  if (UNSTABLE_EVOLUTION_ATK_LOW_LP != 2400)
    while (1)
      ;
  if (UNSTABLE_EVOLUTION_ATK_HIGH_LP != 1000)
    while (1)
      ;
}
#endif
