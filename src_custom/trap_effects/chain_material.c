#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectCHAIN_MATERIAL(void)
{
  struct DuelCard *trapZone;

  Duel_ShowTrapResponseText(CHAIN_MATERIAL, gTrapEffectData.originCardId);

  /* ponytail: Fusion material from Deck/hand/field/GY + cannot attack + End
   * Phase destroy Fusion need fusion/battle/turn hooks. Ceiling: face-up
   * continuous mark (unk4) that Fusion may banish materials broadly. */

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (trapZone != NULL) {
    Duel_ActivateContinuousZone(trapZone);
    trapZone->unk4 = 1;
  }

  UpdateDuelGfxExceptField();
}
