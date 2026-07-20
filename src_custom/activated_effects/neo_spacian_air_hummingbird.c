#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

#define HUMMINGBIRD_LP_PER_CARD 500

static u8 CountOppHandCards(void)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[INACTIVE_DUELIST][i] != NULL
        && gTurnHands[INACTIVE_DUELIST][i]->id != CARD_NONE)
      count++;
  }

  return count;
}

unsigned char CanActivateNEO_SPACIAN_AIR_HUMMINGBIRD(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != NEO_SPACIAN_AIR_HUMMINGBIRD)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != NEO_SPACIAN_AIR_HUMMINGBIRD)
    return FALSE;

  return CanUseMonsterEffect(zone) && CountOppHandCards() > 0;
}

void ActivateNEO_SPACIAN_AIR_HUMMINGBIRDEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 gain;

  Duel_ShowEffectTextTyped(NEO_SPACIAN_AIR_HUMMINGBIRD, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  gain = (u16)CountOppHandCards() * HUMMINGBIRD_LP_PER_CARD;
  if (gain == 0)
    return;

  Duel_ChangeLp(ACTIVE_DUELIST, (s32)gain, TRUE);
  MarkMonsterEffectUsed(zone);
}
