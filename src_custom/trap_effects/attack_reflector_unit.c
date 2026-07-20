#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectATTACK_REFLECTOR_UNIT(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  struct DuelCard *cyber = NULL;
  struct DuelSummonOpts opts;

  Duel_ShowTrapResponseText(ATTACK_REFLECTOR_UNIT, gTrapEffectData.originCardId);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id == CYBER_DRAGON) {
      cyber = zone;
      break;
    }
  }

  if (cyber != NULL) {
    Duel_DestroyZone(cyber, INACTIVE_DUELIST, FALSE);
    if (!ArchlordKristya_IsSpecialSummonLocked()
        && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
      opts = Duel_DefaultSpecialSummonOpts(TRUE);
      if (Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, CYBER_BARRIER_DRAGON, opts)
          != DUEL_ACTION_OK)
        Duel_SpecialSummonFromHand(INACTIVE_DUELIST, CYBER_BARRIER_DRAGON, NULL, opts);
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
