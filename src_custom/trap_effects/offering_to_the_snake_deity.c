#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectOFFERING_TO_THE_SNAKE_DEITY(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  struct DuelCard *reptile = NULL;
  u8 destroyed = 0;
  u8 r;
  u8 c;
  u8 oppRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;

  Duel_ShowTrapResponseText(OFFERING_TO_THE_SNAKE_DEITY, gTrapEffectData.originCardId);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp
        && Duel_CardHasMonsterType(zone->id, TYPE_REPTILE)) {
      reptile = zone;
      break;
    }
  }

  if (reptile != NULL) {
    Duel_DestroyZone(reptile, INACTIVE_DUELIST, FALSE);
    for (r = 0; r < 4 && destroyed < 2; r++) {
      for (c = 0; c < MAX_ZONES_IN_ROW && destroyed < 2; c++) {
        struct DuelCard *zone = gFixedZones[r][c];

        if (zone == NULL || zone->id == CARD_NONE)
          continue;
        /* Prefer opponent cards. */
        if (r != oppRow && r != (oppRow == PLAYER_MONSTER_ROW ? PLAYER_BACKROW
                                                             : OPPONENT_BACKROW))
          continue;
        Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE);
        destroyed++;
        if (IsDuelOver() == TRUE)
          return;
      }
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
