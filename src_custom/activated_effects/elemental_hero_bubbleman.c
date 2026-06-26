#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char CanActivateElementalHeroBubbleman(void) {
  unsigned char i;

  /* Must be face-up on the field */
  if (gMonEffect.id != ELEMENTAL_HERO_BUBBLEMAN)
    return FALSE;

  /* Must control no other cards on the field */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE
        && gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id != ELEMENTAL_HERO_BUBBLEMAN)
      return FALSE;
    if (gTurnZones[ACTIVE_DUELIST_BACKROW][i]->id != CARD_NONE)
      return FALSE;
  }

  /* Must have no cards in hand */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id != CARD_NONE)
      return FALSE;
  }

  return TRUE;
}

void ActivateElementalHeroBubblemanEffect(void) {
  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_BUBBLEMAN, 2);

  /* Draw 2 cards */
  if (Duel_DrawCards(ACTIVE_DUELIST, 2, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}
