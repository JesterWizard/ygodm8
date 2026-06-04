#include "global.h"
#include "board_placement.h"
#include "duel.h"

static u8 Board_ActiveFixedBackrowRow(void) {
  if (WhoseTurn() == DUEL_OPPONENT)
    return OPPONENT_BACKROW;
  return PLAYER_BACKROW;
}

static u8 Board_ActiveFixedMonsterRow(void) {
  if (WhoseTurn() == DUEL_OPPONENT)
    return OPPONENT_MONSTER_ROW;
  return PLAYER_MONSTER_ROW;
}

u8 Board_IsMirroredFixedRow(u8 fixedRow) {
  return fixedRow == OPPONENT_BACKROW || fixedRow == OPPONENT_MONSTER_ROW;
}

u8 Board_PreferredEmptyFixedCol(u8 fixedRow) {
  s8 fixedCol;
  u8 fromRight = Board_IsMirroredFixedRow(fixedRow);

  if (fromRight) {
    for (fixedCol = MAX_ZONES_IN_ROW - 1; fixedCol >= 0; fixedCol--) {
      if (gFixedZones[fixedRow][fixedCol]->id == CARD_NONE)
        return (u8)fixedCol;
    }
  } else {
    for (fixedCol = 0; fixedCol < MAX_ZONES_IN_ROW; fixedCol++) {
      if (gFixedZones[fixedRow][fixedCol]->id == CARD_NONE)
        return (u8)fixedCol;
    }
  }

  return 0xFF;
}

u8 Board_TurnColForZone(u8 turnRow, struct DuelCard *zone) {
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[turnRow][col] == zone)
      return col;
  }

  return 0xFF;
}

u8 Board_PreferredEmptyTurnCol(u8 fixedRow, u8 turnRow) {
  u8 fixedCol = Board_PreferredEmptyFixedCol(fixedRow);

  if (fixedCol == 0xFF)
    return 0xFF;

  return Board_TurnColForZone(turnRow, gFixedZones[fixedRow][fixedCol]);
}

u8 Board_PreferredEmptyMonsterTurnCol(void) {
  u8 fixedRow = Board_ActiveFixedMonsterRow();

  return Board_PreferredEmptyTurnCol(fixedRow, ACTIVE_DUELIST_MONSTER_ROW);
}

u8 Board_PreferredEmptyBackrowTurnCol(void) {
  u8 fixedRow = Board_ActiveFixedBackrowRow();

  return Board_PreferredEmptyTurnCol(fixedRow, ACTIVE_DUELIST_BACKROW);
}
