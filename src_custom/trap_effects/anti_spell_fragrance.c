#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateANTI_SPELL_FRAGRANCEZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, ANTI_SPELL_FRAGRANCE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: both players must Set Spells before activate (next turn) needs spell-activation gate.
   * Ceiling: face-up continuous only; upgrade: spell activate validator requires
   * prior Set + turn delay.
   * Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file. */
}

void TryActivateANTI_SPELL_FRAGRANCEOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(ANTI_SPELL_FRAGRANCE, ActivateANTI_SPELL_FRAGRANCEZone);
}

