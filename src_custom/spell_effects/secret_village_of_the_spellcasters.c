#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void SECRET_VILLAGE_OF_THE_SPELLCASTERS_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(SECRET_VILLAGE_OF_THE_SPELLCASTERS);

  /* ponytail: Spell activation lock based on Spellcaster control needs a
   * Duel_IsCardActivationBlocked / CanActivateSpell gate outside this file
   * (no in-file spell-activate dispatch). Ceiling: continuous face-up only;
   * upgrade: if face-up SECRET_VILLAGE_OF_THE_SPELLCASTERS on field → count
   * Spellcasters you control vs opponent; if only you control any Spellcaster
   * then block opponent TYPE_SPELL activations; if you control none then block
   * your TYPE_SPELL activations. */
}

APPEND_TEXT void EffectSECRET_VILLAGE_OF_THE_SPELLCASTERS(void)
{
  if (Duel_TryResolveSpellThroughTraps(SECRET_VILLAGE_OF_THE_SPELLCASTERS,
                                       SECRET_VILLAGE_OF_THE_SPELLCASTERS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
