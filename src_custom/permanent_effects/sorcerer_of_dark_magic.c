#include "global.h"
#include "duel_helpers.h"

static unsigned char ZoneHasFaceUpSorcererOfDarkMagic(struct DuelCard* zone) {
  return zone->id == SORCERER_OF_DARK_MAGIC && zone->isFaceUp;
}

unsigned char IsSorcererOfDarkMagicTrapLockActive(void) {
  unsigned char i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (ZoneHasFaceUpSorcererOfDarkMagic(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]))
      return TRUE;
  }

  return FALSE;
}
