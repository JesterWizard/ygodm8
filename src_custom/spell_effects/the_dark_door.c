#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "spell_effects.h"
#include "the_dark_door.h"
#include "imperial_order.h"

extern u8 gTheDarkDoorTurnAttackUsed;

u8 IsActivatedTheDarkDoorZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == THE_DARK_DOOR && zone->isFaceUp == TRUE;
}

u8 IsTheDarkDoorActiveOnField(void)
{
  u8 row;
  u8 i;

  if (IsImperialOrderNegatingSpell(THE_DARK_DOOR))
    return FALSE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (gFixedZones[row][i]->id == THE_DARK_DOOR)
        return TRUE;
    }
  }

  return FALSE;
}

u8 TheDarkDoor_CanAttackThisTurn(void)
{
  if (!IsTheDarkDoorActiveOnField())
    return TRUE;

  return !gTheDarkDoorTurnAttackUsed;
}

void TheDarkDoor_MarkAttackUsed(void)
{
  if (IsTheDarkDoorActiveOnField())
    gTheDarkDoorTurnAttackUsed = TRUE;
}

void TheDarkDoor_ResetTurnAttack(void)
{
  gTheDarkDoorTurnAttackUsed = FALSE;
}

APPEND_TEXT void EffectTheDarkDoor(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = THE_DARK_DOOR;
    ActivateCardEffectText();
  }
}
