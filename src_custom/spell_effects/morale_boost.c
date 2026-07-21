#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define MORALE_BOOST_LP_GAIN 1000
#define MORALE_BOOST_DAMAGE 1000

static u8 GetTurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_BACKROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void ChangeLpForActiveMoraleBoosts(s32 delta)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id != MORALE_BOOST || !zone->isFaceUp)
        continue;

      Duel_ChangeLp(GetTurnDuelistForFixedRow(row), delta, TRUE);
      if (IsDuelOver() == TRUE)
        return;
    }
  }
}

void MoraleBoost_OnEquipSpellEquipped(void)
{
  ChangeLpForActiveMoraleBoosts(MORALE_BOOST_LP_GAIN);
}

void MoraleBoost_OnEquipSpellSentFromField(void)
{
  ChangeLpForActiveMoraleBoosts(-MORALE_BOOST_DAMAGE);
}

static void MORALE_BOOST_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(MORALE_BOOST);
}

APPEND_TEXT void EffectMORALE_BOOST(void)
{
  if (Duel_TryResolveSpellThroughTraps(MORALE_BOOST, MORALE_BOOST_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MORALE_BOOST_SelfCheck(void)
{
  if (MORALE_BOOST_LP_GAIN != 1000)
    while (1)
      ;
  if (MORALE_BOOST_DAMAGE != 1000)
    while (1)
      ;
}
#endif
