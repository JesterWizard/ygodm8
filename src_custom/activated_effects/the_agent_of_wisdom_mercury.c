#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateTHE_AGENT_OF_WISDOM_MERCURY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THE_AGENT_OF_WISDOM_MERCURY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THE_AGENT_OF_WISDOM_MERCURY)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * Once via usage if hand empty (standby/end-phase gate not wired). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0;
}

void ActivateTHE_AGENT_OF_WISDOM_MERCURYEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(THE_AGENT_OF_WISDOM_MERCURY, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) != 0)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
