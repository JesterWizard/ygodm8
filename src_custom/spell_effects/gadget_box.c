#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define GADGET_BOX_START_COUNTERS 3
/* ponytail: no dedicated Gadget Box Token card id — reuse MOON_TOKEN like other
 * token spells. Ceiling: wrong printed name/stats; upgrade: real token card. */
#define GADGET_BOX_TOKEN_ID MOON_TOKEN

static void GADGET_BOX_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  if (zone != NULL)
    zone->unk4 = GADGET_BOX_START_COUNTERS;

  Duel_ShowEffectText(GADGET_BOX);

  /* ponytail: OPT remove 1 Morph Counter → SS Gadget Box Token + ED Synchro-only
   * lock while Token present need Main Phase ignition + SS gate outside this
   * file. Ceiling: continuous face-up with unk4=3 counters only; upgrade:
   * ignition → unk4-- → Duel_SpecialSummonMonsterId(GADGET_BOX_TOKEN_ID) +
   * ED lock flag. */
  (void)GADGET_BOX_TOKEN_ID;
  (void)ArchlordKristya_IsSpecialSummonLocked;
}

APPEND_TEXT void EffectGADGET_BOX(void)
{
  if (Duel_TryResolveSpellThroughTraps(GADGET_BOX, GADGET_BOX_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
