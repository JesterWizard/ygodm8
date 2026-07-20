#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectMETEORAIN(void)
{
  struct DuelCard *trapZone =
      gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  Duel_ShowTrapResponseText(METEORAIN, gTrapEffectData.originCardId);

  if (trapZone != NULL) {
    Duel_ActivateContinuousZone(trapZone);
    trapZone->unk4 = 1;
  }

  UpdateDuelGfxExceptField();

  /* ponytail: this turn your monsters inflict piercing needs battle damage
   * calc hook + End Phase leave. Ceiling: face-up continuous mark; upgrade:
   * battle ATK>DEF vs Defense → piercing while METEORAIN face-up this turn. */
}
