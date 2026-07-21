#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_attack_restrictions.h"
#include "duel_helpers.h"
#include "gravity_bind.h"
#include "level_limit_area_b.h"
#include "vengeful_bog_spirit.h"
#include "wall_of_revealing_light.h"
#include "nightmare_wheel.h"
#include "harpie_lady_3.h"
#include "spell_effects.h"

void Duel_ResetAttackRestrictions(void)
{
  gDuelAttackRestrictionsActive = 0;
}

void Duel_RefreshAttackRestrictions(void)
{
  u8 flags = 0;
  u8 currentTurn;

  /* Decrement Harpie Lady 3 attack-lock turn counters once per turn change */
  currentTurn = WhoseTurn();
  if (currentTurn != gHarpieLady3LastProcessedTurn) {
    u8 i;
    for (i = 0; i < 10; i++) {
      if (gHarpieLady3RestrictTurns[i] > 0)
        gHarpieLady3RestrictTurns[i]--;
    }
    gHarpieLady3LastProcessedTurn = currentTurn;
  }

  if (gTurnDuelistBattleState[ACTIVE_DUELIST]->sorlTurns)
    flags |= DUEL_ATTACK_RESTRICT_SORL;

  if (Duel_IsBackrowCardOnField(GRAVITY_BIND, FALSE))
    flags |= DUEL_ATTACK_RESTRICT_GRAVITY_BIND;

  if (IsLevelLimitAreaBActiveOnField())
    flags |= DUEL_ATTACK_RESTRICT_LEVEL_LIMIT_AREA_B;

  if (IsVengefulBogSpiritActiveOnField())
    flags |= DUEL_ATTACK_RESTRICT_VENGEFUL_BOG_SPIRIT;

  if (IsWallOfRevealingLightActiveOnField())
    flags |= DUEL_ATTACK_RESTRICT_WALL_OF_REVEALING_LIGHT;
  else
    WallOfRevealingLight_ClearThreshold();

  gDuelAttackRestrictionsActive = flags;
}

u8 SphereMode_CanDeclareAttack(const struct DuelCard *zone);

u8 Duel_CanMonsterDeclareAttackWithCachedRestrictions(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &fixedCol)
      && MysticMine_LocksFixedDuelist(Duel_FixedDuelistForMonsterRow(fixedRow)))
    return FALSE;

  if (!SphereMode_CanDeclareAttack(zone))
    return FALSE;

  if (!MaskOfTheAccursed_CanMonsterDeclareAttack(zone))
    return FALSE;

  if (gDuelAttackRestrictionsActive == 0)
    return TRUE;

  if (gDuelAttackRestrictionsActive & DUEL_ATTACK_RESTRICT_SORL)
    return FALSE;

  if ((gDuelAttackRestrictionsActive & DUEL_ATTACK_RESTRICT_GRAVITY_BIND)
      && !GravityBind_CanMonsterAttack(zone->id))
    return FALSE;

  if ((gDuelAttackRestrictionsActive & DUEL_ATTACK_RESTRICT_LEVEL_LIMIT_AREA_B)
      && !LevelLimitAreaB_CanMonsterAttack(zone))
    return FALSE;

  if ((gDuelAttackRestrictionsActive & DUEL_ATTACK_RESTRICT_VENGEFUL_BOG_SPIRIT)
      && !VengefulBogSpirit_CanMonsterAttack(zone))
    return FALSE;

  if ((gDuelAttackRestrictionsActive & DUEL_ATTACK_RESTRICT_WALL_OF_REVEALING_LIGHT)
      && !WallOfRevealingLight_CanMonsterAttack(zone))
    return FALSE;

  if (!NightmareWheel_CanMonsterDeclareAttack(zone))
    return FALSE;

  /* Harpie Lady 3: check per-zone attack lock */
  {
    u8 fixedRow;
    u8 col;
    u8 offset;

    if (Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col)) {
      offset = (fixedRow == 1) ? 5 : 0;
      if (gHarpieLady3RestrictTurns[offset + col] > 0)
        return FALSE;
    }
  }

  return TRUE;
}

u8 Duel_CanMonsterDeclareAttack(const struct DuelCard *zone)
{
  Duel_RefreshAttackRestrictions();
  return Duel_CanMonsterDeclareAttackWithCachedRestrictions(zone);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DuelAttackRestrictions_SelfCheck(void)
{
  u8 saved = gDuelAttackRestrictionsActive;

  Duel_ResetAttackRestrictions();
  if (gDuelAttackRestrictionsActive != 0)
    __builtin_trap();

  gDuelAttackRestrictionsActive = DUEL_ATTACK_RESTRICT_SORL;
  if (!(gDuelAttackRestrictionsActive & DUEL_ATTACK_RESTRICT_SORL))
    __builtin_trap();

  gDuelAttackRestrictionsActive = saved;
}
#endif
