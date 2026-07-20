#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateDRAGON_S_RAGEZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, DRAGON_S_RAGE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: Dragon piercing needs battle damage calc hook outside this file.
   * Ceiling: face-up continuous only; upgrade: if face-up DRAGON_S_RAGE and
   * attacker TYPE_DRAGON vs Defense Position → piercing. */
}

void TryActivateDRAGON_S_RAGEOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(DRAGON_S_RAGE, ActivateDRAGON_S_RAGEZone);
}

/* ponytail: wire TryActivate into turn_effect_hooks. */
