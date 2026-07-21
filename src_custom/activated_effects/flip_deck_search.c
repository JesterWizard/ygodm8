#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "flip_deck_search.h"
#include "monster_effect_usage.h"

unsigned char CanActivateA_CAT_OF_ILL_OMEN(void);
void ActivateA_CAT_OF_ILL_OMENEffect(void);
unsigned char CanActivateAN_OWL_OF_LUCK(void);
void ActivateAN_OWL_OF_LUCKEffect(void);

void TryActivateFlipDeckSearchOnFaceUp(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || !zone->isFaceUp)
    return;
  if (zone->id != A_CAT_OF_ILL_OMEN && zone->id != AN_OWL_OF_LUCK)
    return;
  if (!CanUseMonsterEffect(zone))
    return;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return;

  gMonEffect.id = zone->id;
  gMonEffect.row = fixedRow;
  gMonEffect.zone = col;

  if (zone->id == A_CAT_OF_ILL_OMEN) {
    if (!CanActivateA_CAT_OF_ILL_OMEN()) {
      gMonEffect.id = CARD_NONE;
      return;
    }
    ActivateA_CAT_OF_ILL_OMENEffect();
  } else {
    if (!CanActivateAN_OWL_OF_LUCK()) {
      gMonEffect.id = CARD_NONE;
      return;
    }
    ActivateAN_OWL_OF_LUCKEffect();
  }

  gMonEffect.id = CARD_NONE;
}
