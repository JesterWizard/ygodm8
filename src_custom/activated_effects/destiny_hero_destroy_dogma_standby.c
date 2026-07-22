#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_destroy_dogma.h"
#include "duel_helpers.h"

void TryApplyDestinyHeroDestroyDogmaStandby(void)
{
  u8 standbyFixed = WhoseTurn();
  u8 controllerFixed = standbyFixed == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 row = Duel_FixedMonsterRowForDuelist(controllerFixed);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id != DESTINY_HERO_DESTROY_DOGMA)
      continue;

    Duel_ShowEffectTextTyped(DESTINY_HERO_DESTROY_DOGMA, 2);
    Duel_ChangeLp(standbyFixed, -2000, TRUE);
    return;
  }
}
