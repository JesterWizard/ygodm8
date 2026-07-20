#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateELEMENTAL_HERO_MARINE_NEOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_MARINE_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_MARINE_NEOS)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) > 0;
}

void ActivateELEMENTAL_HERO_MARINE_NEOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s8 handZone;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_MARINE_NEOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
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
