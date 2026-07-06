#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

static u8 IsFaceUpEraserOnField(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != THE_WICKED_ERASER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

unsigned char CanActivateTheWickedEraser(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THE_WICKED_ERASER)
    return FALSE;

  if (gMonEffect.row != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return IsFaceUpEraserOnField(zone);
}

void ActivateTheWickedEraserEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}
