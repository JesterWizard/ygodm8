#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "needle_wall.h"

void UpdateDuelGfxExceptField(void);

static void NeedleWallRollDestroy(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 roll;
  u8 attempts = 0;

  do {
    roll = RandRangeU8(1, 6);
    attempts++;
  } while (roll == 6 && attempts < 8);

  if (roll >= 1 && roll <= 5) {
    u8 col = 5 - roll; /* 1→col4, 5→col0 */
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id != CARD_NONE)
      Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE);
  }
}

static void ActivateNEEDLE_WALLZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, NEEDLE_WALL) == DUEL_ACTION_DUEL_OVER)
    return;

  NeedleWallRollDestroy();
}

void TryActivateNEEDLE_WALLOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(NEEDLE_WALL, ActivateNEEDLE_WALLZone);
}

void TryApplyNeedleWallStandby(void)
{
  u8 col;
  struct DuelCard *zone;

  if (IsDuelOver() == TRUE)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];
    if (zone == NULL || zone->id != NEEDLE_WALL || zone->isFaceUp == FALSE)
      continue;

    NeedleWallRollDestroy();
    if (IsDuelOver() == TRUE)
      return;
  }
}
