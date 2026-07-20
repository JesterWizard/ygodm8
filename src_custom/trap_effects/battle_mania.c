#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectBATTLE_MANIA(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;

  Duel_ShowTrapResponseText(BATTLE_MANIA, gTrapEffectData.originCardId);

  /* ponytail: activate only opp Standby. Ceiling: when Effect runs, flip opp
   * monsters to ATK; forced-attack / cannot-change-position need battle gates. */

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    zone->isFaceUp = TRUE;
    zone->isDefending = FALSE;
    zone->unk4 |= 1; /* mark: cannot change position / must attack */
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
