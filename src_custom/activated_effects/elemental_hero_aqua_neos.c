#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateELEMENTAL_HERO_AQUA_NEOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_AQUA_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_AQUA_NEOS)
    return FALSE;

  /* ponytail: Contact fusion need fusion hook; EP Extra return via
   * TryReturnContactFusionsAtEndPhase. Ceiling: OPT discard 1, then destroy 1
   * random opponent hand card. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) > 0
      && Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) > 0;
}

void ActivateELEMENTAL_HERO_AQUA_NEOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s8 handZone;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_AQUA_NEOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0)
    return;

  handZone = Duel_PickRandomHandZone(INACTIVE_DUELIST);
  if (handZone < 0)
    return;

  if (Duel_DestroyZone(gTurnHands[INACTIVE_DUELIST][handZone], INACTIVE_DUELIST, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
