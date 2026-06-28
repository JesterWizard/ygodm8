#include "global.h"
#include "common-chax.h"
#include "autonomous_action_unit.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define AUTONOMOUS_ACTION_UNIT_LP_COST 1500

static u8 IsMonsterCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 ActiveDuelistHasLpForCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= AUTONOMOUS_ACTION_UNIT_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= AUTONOMOUS_ACTION_UNIT_LP_COST;
}

static struct DuelCard *FindSummonedMonsterZone(u16 monsterId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id == monsterId)
      return zone;
  }

  return NULL;
}

u8 CanActivateAutonomousActionUnit(void)
{
  if (!ActiveDuelistHasLpForCost())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!IsMonsterCard(gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard))
    return FALSE;

  return TRUE;
}

static void AutonomousActionUnit_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u16 monsterId;
  struct DuelCard *summonedZone;

  Duel_ShowEffectText(AUTONOMOUS_ACTION_UNIT);

  if (IsDuelOver() == TRUE || !CanActivateAutonomousActionUnit())
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -AUTONOMOUS_ACTION_UNIT_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE || !CanActivateAutonomousActionUnit())
    return;

  monsterId = GetGraveCardAndClearGrave(INACTIVE_DUELIST);
  if (!IsMonsterCard(monsterId))
    return;

  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, monsterId, opts) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  summonedZone = FindSummonedMonsterZone(monsterId);
  if (summonedZone == NULL)
    return;

  if (!RegisterDynamicEquip(spellZone, summonedZone, AUTONOMOUS_ACTION_UNIT, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
}

APPEND_TEXT void EffectAutonomousActionUnit(void)
{
  if (Duel_TryResolveSpellThroughTrapsEx(AUTONOMOUS_ACTION_UNIT, AUTONOMOUS_ACTION_UNIT_LP_COST,
                                         AutonomousActionUnit_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
