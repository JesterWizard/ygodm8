#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

unsigned char CanActivateTOHUSHADDOLL_GRYSTA(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != TOHUSHADDOLL_GRYSTA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != TOHUSHADDOLL_GRYSTA)
    return FALSE;

  /* ponytail: FLIP copy + GY Fusion-by-banish need flip/GY hooks.
   * Ceiling: OPT add Shaddoll Fusion from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, SHADDOLL_FUSION) >= 0;
}

void ActivateTOHUSHADDOLL_GRYSTAEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(TOHUSHADDOLL_GRYSTA, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, SHADDOLL_FUSION, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
