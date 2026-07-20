#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/card_enums.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "riryoku.h"
#include "spell_effects.h"

#define WEAPON_CHANGE_LP_COST 700

void UpdateDuelGfxExceptField(void);

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsWarriorOrMachine(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_WARRIOR)
      || Duel_CardHasMonsterType(cardId, TYPE_MACHINE);
}

static u8 IsValidWeaponChangeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsWarriorOrMachine(zone->id);
}

static u8 HasWeaponChangeTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidWeaponChangeTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 CanPayWeaponChangeCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= WEAPON_CHANGE_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= WEAPON_CHANGE_LP_COST;
}

static u8 CanActivateWeaponChangeIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != WEAPON_CHANGE || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  if (!CanPayWeaponChangeCost())
    return FALSE;

  return HasWeaponChangeTarget();
}

static void GetZoneFinalAtkDef(struct DuelCard *zone, u16 *outAtk, u16 *outDef)
{
  if (zone == NULL || zone->id == CARD_NONE) {
    *outAtk = 0;
    *outDef = 0;
    return;
  }

  gStatMod.card = zone->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(zone);
  gSetFinalStatZone = zone;
  SetFinalStat(&gStatMod);
  *outAtk = gCardInfo.atk;
  *outDef = gCardInfo.def;
  gSetFinalStatZone = NULL;
}

static void ApplyAtkDefSwap(struct DuelCard *zone)
{
  u16 atk;
  u16 def;
  s16 delta;

  GetZoneFinalAtkDef(zone, &atk, &def);
  delta = (s16)((s32)def - (s32)atk);
  if (delta != 0)
    AddRiryokuAtkDelta(zone, delta);

  /* ponytail: Riryoku only adjusts ATK — DEF does not become the old ATK from
   * this file alone. Ceiling: ATK becomes current DEF; DEF unchanged.
   * Upgrade: ShieldAndSword-style per-zone swap flag in SetFinalStat that swaps
   * both stats until end of opponent's next turn. */
  /* ponytail: duration is "until end of opponent's next turn" but Riryoku
   * deltas clear every End Phase (ClearAllRiryokuAtkDeltas). Ceiling: lasts
   * until next EOT clear; upgrade: turn_effect_hooks 2-End-Phase counter. */

  RefreshFieldMonsterStatOverlays();
}

static void CancelWeaponChangeTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  UpdateDuelGfxExceptField();
}

static u8 AiPickWeaponChangeTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidWeaponChangeTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveWeaponChangeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target;

  if (!IsValidWeaponChangeTarget(fixedRow, fixedCol))
    return;

  target = gFixedZones[fixedRow][fixedCol];
  ApplyAtkDefSwap(target);

  if (spellZone != NULL)
    spellZone->effectUsedThisTurn = TRUE;
}

static void ResolveWeaponChangeIgnition(struct DuelCard *zone)
{
  if (!CanActivateWeaponChangeIgnition(zone))
    return;

  Duel_ShowEffectText(WEAPON_CHANGE);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -WEAPON_CHANGE_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (!HasWeaponChangeTarget())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  if (WhoseTurn() != DUEL_PLAYER) {
    u8 row;
    u8 col;

    if (AiPickWeaponChangeTarget(&row, &col))
      ResolveWeaponChangeTarget(row, col);
    return;
  }

  Duel_SetupPickZone(IsValidWeaponChangeTarget, ResolveWeaponChangeTarget,
                     CancelWeaponChangeTargeting, AiPickWeaponChangeTarget);
  Duel_EnterPickZoneTargeting();
}

static void WEAPON_CHANGE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up continuous (OPT ignition; printed = Standby). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateWeaponChangeIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveWeaponChangeIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(WEAPON_CHANGE);

  /* ponytail: printed "once during each of your Standby Phases" needs a
   * turn_effect_hooks Standby gate outside this file. Ceiling: face-up OPT
   * ignition any phase (Main-style re-activate); upgrade: Standby-only
   * CanActivate + auto-prompt, or GetSpellType NORMAL list like CALL_OF_THE_MUMMY. */
}

APPEND_TEXT void EffectWEAPON_CHANGE(void)
{
  if (Duel_TryResolveSpellThroughTraps(WEAPON_CHANGE, WEAPON_CHANGE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void WEAPON_CHANGE_SelfCheck(void)
{
  if (WEAPON_CHANGE_LP_COST != 700)
    while (1)
      ;
  if (!Duel_CardHasMonsterType(GAIA_THE_FIERCE_KNIGHT, TYPE_WARRIOR))
    while (1)
      ;
  if (!Duel_CardHasMonsterType(CYBER_DRAGON, TYPE_MACHINE))
    while (1)
      ;
}
#endif
