#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void COLD_WAVE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(COLD_WAVE);

  if (IsDuelOver() == TRUE)
    return;

  /* ponytail: "activate only at start of Main Phase 1" needs a phase/action
   * counter outside this file (no Main Phase 1-start gate API). Ceiling: activable
   * any time like a normal spell; upgrade: CanActivate → require MP1 + no prior
   * play/set/summon this turn. */

  /* ponytail: block play/Set of Spell/Trap until next turn needs a shared lock
   * hooked into Duel_IsCardActivationBlocked / set-from-hand (like Wicked Avatar
   * SpellTrap lock). Ceiling: show text + send to GY only; upgrade: arm a Cold
   * Wave turn flag in Duel_IsCardActivationBlocked for TYPE_SPELL/TRAP and Set
   * paths until activator's next Standby, then clear. */

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectCOLD_WAVE(void)
{
  if (Duel_TryResolveSpellThroughTraps(COLD_WAVE, COLD_WAVE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
