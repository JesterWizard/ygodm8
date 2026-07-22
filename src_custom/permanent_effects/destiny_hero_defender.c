#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_defender.h"
#include "duel_helpers.h"

static u8 InactiveDuelistHasFaceUpDefDefender(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == DESTINY_HERO_DEFENDER && zone->isFaceUp
        && zone->isDefending)
      return TRUE;
  }

  return FALSE;
}

void TryApplyDestinyHeroDefenderStandbyDraw(void)
{
  if (IsDuelOver() == TRUE || !InactiveDuelistHasFaceUpDefDefender())
    return;

  if (FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]) < 0)
    return;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DEFENDER, 9);
  if (IsDuelOver() == TRUE)
    return;

  Duel_DrawCards(INACTIVE_DUELIST, 1, TRUE);
}

unsigned char ShouldActivateDESTINY_HERO_DEFENDER(void)
{
  /* Opp Standby draw while face-up DEF via TryApplyDestinyHeroDefenderStandbyDraw. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateDESTINY_HERO_DEFENDER(void)
{
}
