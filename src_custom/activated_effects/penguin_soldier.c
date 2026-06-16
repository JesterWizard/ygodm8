#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

unsigned char CanActivatePenguinSoldier(void)
{
  u8 enemyRow;
  u8 i;

  if (gMonEffect.id != PENGUIN_SOLDIER)
    return FALSE;

  if (gMonEffect.row != 1 && gMonEffect.row != 2)
    return FALSE;

  if (NumEmptyZonesInRow(gTurnHands[INACTIVE_DUELIST]) == 0)
    return FALSE;

  enemyRow = (gMonEffect.row == 1) ? 2 : 1;
  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gTurnZones[enemyRow][i]->id != CARD_NONE)
      return TRUE;

  return FALSE;
}

static unsigned char ReturnEnemyMonsterToOpponentHand(u8 enemyRow)
{
  u8 sourceZone;

  if (NumEmptyZonesInRow(gTurnHands[INACTIVE_DUELIST]) == 0)
    return FALSE;

  for (sourceZone = 0; sourceZone < MAX_ZONES_IN_ROW; sourceZone++)
  {
    struct DuelCard *zone = gTurnZones[enemyRow][sourceZone];

    if (zone->id == CARD_NONE)
      continue;

    if (Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK)
      return TRUE;

    return FALSE;
  }

  return FALSE;
}

void ActivatePenguinSoldierEffect(void)
{
  u8 enemyRow = (gMonEffect.row == 1) ? 2 : 1;
  u8 returned = 0;

  while (returned < 2 && ReturnEnemyMonsterToOpponentHand(enemyRow))
    returned++;

  Duel_ShowEffectTextTyped(PENGUIN_SOLDIER, 2);
}
