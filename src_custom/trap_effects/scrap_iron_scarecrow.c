#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);
void LockMonsterCardsInRow(unsigned char turnRow);

APPEND_TEXT void EffectSCRAP_IRON_SCARECROW(void)
{
  struct DuelCard *trapZone =
      gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  Duel_ShowTrapResponseText(SCRAP_IRON_SCARECROW, gTrapEffectData.originCardId);

  LockMonsterCardsInRow(ACTIVE_DUELIST_MONSTER_ROW);

  if (trapZone != NULL) {
    trapZone->isFaceUp = FALSE;
    trapZone->isLocked = FALSE;
  }

  UpdateDuelGfxExceptField();
}
