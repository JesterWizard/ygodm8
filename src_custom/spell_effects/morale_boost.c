#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define MORALE_BOOST_LP_GAIN 1000
#define MORALE_BOOST_DAMAGE 1000

static void MORALE_BOOST_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(MORALE_BOOST);

  /* ponytail: equip-on / equip-off LP swing needs field/equip hooks outside this
   * file (RegisterDynamicEquip / OnDynamicEquipZoneAboutToClear / vanilla equip
   * attach-detach). Ceiling: continuous face-up only; upgrade: when any Equip
   * Spell equips → Duel_ChangeLp(controller, +MORALE_BOOST_LP_GAIN); when any
   * Equip Spell leaves field → Duel_ChangeLp(controller, -MORALE_BOOST_DAMAGE). */

  (void)MORALE_BOOST_LP_GAIN;
  (void)MORALE_BOOST_DAMAGE;
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
