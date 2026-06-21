#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "spell_effects.h"
#include "imperial_order.h"

#define CHAIN_ENERGY_LP_COST 500

u8 IsActivatedChainEnergyZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == CHAIN_ENERGY && zone->isFaceUp == TRUE;
}

u8 IsChainEnergyActiveOnField(void)
{
  u8 row;
  u8 i;

  if (IsImperialOrderNegatingSpell(CHAIN_ENERGY))
    return FALSE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (IsActivatedChainEnergyZone(gFixedZones[row][i]))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 ActiveDuelistCanPayChainEnergyCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= CHAIN_ENERGY_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= CHAIN_ENERGY_LP_COST;
}

static void ApplyChainEnergyLpCost(void)
{
  if (Duel_ChangeLp(ACTIVE_DUELIST, -CHAIN_ENERGY_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}

u8 TryPayChainEnergyCost(void)
{
  if (!IsChainEnergyActiveOnField())
    return TRUE;

  if (!ActiveDuelistCanPayChainEnergyCost())
    return FALSE;

  ApplyChainEnergyLpCost();

  return IsDuelOver() != TRUE;
}

u8 IsActiveDuelistHandZone(const struct DuelCard *zone)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i] == zone)
      return TRUE;
  }

  return FALSE;
}

static u8 IsTurnFieldZone(const struct DuelCard *zone)
{
  u8 row;
  u8 i;

  for (row = 0; row < ACTIVE_DUELIST_HAND; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (gTurnZones[row][i] == zone)
        return TRUE;
    }
  }

  return FALSE;
}

u8 ShouldPayChainEnergyForHandToFieldCopy(const struct DuelCard *dst, const struct DuelCard *src)
{
  if (!IsChainEnergyActiveOnField())
    return FALSE;

  return IsActiveDuelistHandZone(src) && IsTurnFieldZone(dst);
}

APPEND_TEXT void EffectChainEnergy(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(CHAIN_ENERGY);
}
