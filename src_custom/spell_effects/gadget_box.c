#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

/* ponytail: no dedicated Gadget Box Token card id — reuse MOON_TOKEN like other
 * token spells. Ceiling: wrong printed name/stats; upgrade: real token card. */
#define GADGET_BOX_TOKEN_ID MOON_TOKEN

/* ponytail: OPT remove 1 Morph Counter → SS Gadget Box Token + ED Synchro-only
 * lock while Token present need Main Phase ignition + SS gate outside this
 * file. Ceiling: continuous face-up with unk4=3 counters only; upgrade:
 * ignition → unk4-- → Duel_SpecialSummonMonsterId(GADGET_BOX_TOKEN_ID) +
 * ED lock flag. */

APPEND_TEXT void EffectGADGET_BOX(void)
{
  const struct EffectScript *script = EffectScript_Find(GADGET_BOX, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);

  (void)GADGET_BOX_TOKEN_ID;
  (void)ArchlordKristya_IsSpecialSummonLocked;
}
