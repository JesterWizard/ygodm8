#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectRISE_OF_THE_SNAKE_DEITY(void)
{
  struct DuelSummonOpts opts;

  Duel_ShowTrapResponseText(RISE_OF_THE_SNAKE_DEITY, gTrapEffectData.originCardId);

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHand(INACTIVE_DUELIST, VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES,
                                 NULL, opts) != DUEL_ACTION_OK)
    Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES,
                               opts);

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
