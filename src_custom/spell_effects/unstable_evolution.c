#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define UNSTABLE_EVOLUTION_ATK_LOW_LP 2400
#define UNSTABLE_EVOLUTION_ATK_HIGH_LP 1000

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u16 ControllerLifePoints(void)
{
  return WhoseTurn() == DUEL_PLAYER ? gDuelLifePoints[DUEL_PLAYER]
                                    : gDuelLifePoints[DUEL_OPPONENT];
}

static u16 OpponentLifePoints(void)
{
  return WhoseTurn() == DUEL_PLAYER ? gDuelLifePoints[DUEL_OPPONENT]
                                    : gDuelLifePoints[DUEL_PLAYER];
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

static u16 DesiredOriginalAtk(void)
{
  u16 myLp = ControllerLifePoints();
  u16 oppLp = OpponentLifePoints();

  if (myLp < oppLp)
    return UNSTABLE_EVOLUTION_ATK_LOW_LP;
  if (myLp > oppLp)
    return UNSTABLE_EVOLUTION_ATK_HIGH_LP;
  return 0xFFFF; /* equal LP — neither clause; leave ATK alone */
}

static s8 StagesToReachOriginalAtk(u16 cardId, u16 targetAtk)
{
  s32 needed;

  if (targetAtk == 0xFFFF)
    return 0;

  SetCardInfo(cardId);
  needed = (s32)targetAtk - (s32)gCardInfo.atk;

  /* 1 stage ~= 500 ATK; nearest stage (same rounding as Triangle Ecstasy Spark). */
  if (needed >= 0)
    return (s8)((needed + 250) / 500);
  return (s8)((needed - 250) / 500);
}

static void EquipUnstableEvolution(struct DuelCard *spellZone, struct DuelCard *target)
{
  u16 desired = DesiredOriginalAtk();
  s8 stages = StagesToReachOriginalAtk(target->id, desired);
  u8 applied = 0;

  if (stages > 0) {
    applied = (u8)stages;
    ApplyDynamicEquipStages(target, applied);
  } else if (stages < 0) {
    s8 left = stages;

    /* Bit7 marks ATK-cut path so Remove restores via IncrementPermStage. */
    applied = (u8)((-stages) | 0x80);
    while (left < 0) {
      DecrementPermStage(target);
      left++;
    }
  }

  if (!RegisterDynamicEquip(spellZone, target, UNSTABLE_EVOLUTION, applied))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
  Duel_NotifyMonsterZoneChanged(target);
  Duel_RefreshMonsterStatOverlays();

  /* ponytail: LP-conditional original ATK (2400 if lower / 1000 if higher) needs
   * continuous refresh while equipped when LP changes, plus exact original-ATK
   * overlay (stage unit is 500). Ceiling: one-shot nearest-stage adjust at equip
   * from printed original; equal LP leaves ATK unchanged.
   * Upgrade: card_info / RecalculateDynamicEquips → if DynamicEquipTargetsMonster
   * WithSpell(UNSTABLE_EVOLUTION) force original ATK from controller vs opp LP. */
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
