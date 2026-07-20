#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void ANCIENT_GEAR_CASTLE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  if (zone != NULL)
    zone->unk4 = 0;

  Duel_ShowEffectText(ANCIENT_GEAR_CASTLE);

  /* ponytail: +300 ATK for Ancient Gear monsters needs a continuous field-stat
   * applier outside this file (Duel_TryApplyDynamicZoneStats only covers
   * registered monster ids; 1 stage ~= 500 ATK so printed +300 is not exact).
   * Ceiling: continuous face-up only; upgrade: LynJump/stat overlay → if
   * face-up ANCIENT_GEAR_CASTLE and Duel_CardNameContains(id, "Ancient Gear")
   * then ATK += 300 (exact overlay). */

  /* ponytail: Counter on each Normal Summon/Set needs a summon/set hook
   * outside this file (no in-file summon dispatch). Ceiling: unk4 stays 0;
   * upgrade: after Normal Summon/Set → if face-up ANCIENT_GEAR_CASTLE on
   * controller's field then zone->unk4++. */

  /* ponytail: Tribute this card instead when Tribute Summoning an Ancient Gear
   * (if counters >= required Tributes) needs a tribute-count / substitute hook
   * outside this file. Ceiling: never substitutes; upgrade: tribute gate → if
   * face-up ANCIENT_GEAR_CASTLE && unk4 >= required && summoning Ancient Gear
   * then destroy this card as the Tribute(s). */
}

APPEND_TEXT void EffectANCIENT_GEAR_CASTLE(void)
{
  if (Duel_TryResolveSpellThroughTraps(ANCIENT_GEAR_CASTLE, ANCIENT_GEAR_CASTLE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
