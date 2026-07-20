#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

unsigned char CanActivateBIRDFACE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BIRDFACE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BIRDFACE)
    return FALSE;

  /* ponytail: battle-destroy→GY trigger. Ceiling: once via usage if Harpie Lady
   * in Deck and hand space. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, HARPIE_LADY) >= 0;
}

void ActivateBIRDFACEEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(BIRDFACE, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  Duel_AddDeckCardToHand(ACTIVE_DUELIST, HARPIE_LADY, TRUE);
  MarkMonsterEffectUsed(zone);
  UpdateDuelGfxExceptField();
}
