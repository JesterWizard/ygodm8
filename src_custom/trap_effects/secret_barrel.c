#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "secret_barrel.h"

#define SECRET_BARREL_DAMAGE_PER_CARD 200

static u8 CountActiveDuelistFieldAndHandCards(void)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE)
      count++;
    if (gTurnZones[ACTIVE_DUELIST_BACKROW][i]->id != CARD_NONE)
      count++;
    if (gTurnHands[ACTIVE_DUELIST][i]->id != CARD_NONE)
      count++;
  }

  return count;
}

static void ActivateSecretBarrelZone(struct DuelCard *zone)
{
  u8 cardCount = CountActiveDuelistFieldAndHandCards();
  u16 damage;

  if (Duel_ActivateContinuousTrapPreamble(zone, SECRET_BARREL) == DUEL_ACTION_DUEL_OVER)
    return;

  if (cardCount == 0)
    return;

  damage = (u16)cardCount * SECRET_BARREL_DAMAGE_PER_CARD;
  Duel_ChangeLp(ACTIVE_DUELIST, -(s32)damage, FALSE);
}

void TryActivateSecretBarrelOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(SECRET_BARREL, ActivateSecretBarrelZone);
}
