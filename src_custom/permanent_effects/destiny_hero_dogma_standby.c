#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_dogma_standby.h"
#include "duel_helpers.h"

void TryApplyDestinyHeroDogmaStandby(void)
{
  u8 standbyFixed = WhoseTurn();
  u8 dogmaOwnerFixed = standbyFixed == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 row = Duel_FixedMonsterRowForDuelist(dogmaOwnerFixed);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];
    u16 lp;
    s32 pay;

    if (zone == NULL || !zone->isFaceUp || zone->id != DESTINY_HERO_DOGMA)
      continue;
    if (zone->unk4 != 1)
      continue;

    Duel_ShowEffectTextTyped(DESTINY_HERO_DOGMA, 2);
    lp = gDuelLifePoints[standbyFixed];
    pay = (s32)(lp / 2);
    if (pay > 0) {
      if (Duel_ChangeLp(standbyFixed, -pay, TRUE) == DUEL_ACTION_DUEL_OVER)
        return;
    }

    zone->unk4 = 2;
    return;
  }
}
