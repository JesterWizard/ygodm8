#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectICARUS_ATTACK(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  struct DuelCard *tribute = NULL;
  u8 destroyed = 0;
  u8 r;
  u8 c;

  Duel_ShowTrapResponseText(ICARUS_ATTACK, gTrapEffectData.originCardId);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && Duel_CardHasMonsterType(zone->id, TYPE_WINGED_BEAST)) {
      tribute = zone;
      break;
    }
  }

  if (tribute != NULL) {
    Duel_DestroyZone(tribute, INACTIVE_DUELIST, FALSE);

    for (r = 0; r < 4 && destroyed < 2; r++) {
      for (c = 0; c < MAX_ZONES_IN_ROW && destroyed < 2; c++) {
        struct DuelCard *zone = gFixedZones[r][c];

        if (zone == NULL || zone->id == CARD_NONE || zone == tribute)
          continue;
        Duel_DestroyZone(zone, DUEL_PLAYER, FALSE);
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
