#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

#define ROYAL_MAGICAL_LIBRARY_COUNTER_COST 3

unsigned char CanActivateROYAL_MAGICAL_LIBRARY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ROYAL_MAGICAL_LIBRARY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ROYAL_MAGICAL_LIBRARY)
    return FALSE;

  /* Spell Counters on resolve via TryIncrementSpellCountersOnSpellResolve.
   * Ceiling: ignition only when unk4>=3. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return zone->unk4 >= ROYAL_MAGICAL_LIBRARY_COUNTER_COST;
}

void ActivateROYAL_MAGICAL_LIBRARYEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ROYAL_MAGICAL_LIBRARY, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (self->unk4 < ROYAL_MAGICAL_LIBRARY_COUNTER_COST)
    return;

  self->unk4 = (u8)(self->unk4 - ROYAL_MAGICAL_LIBRARY_COUNTER_COST);

  if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
