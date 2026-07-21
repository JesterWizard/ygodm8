#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectDAMAGE_POLARIZER(void)
{
  Duel_ShowTrapResponseText(DAMAGE_POLARIZER, gTrapEffectData.originCardId);

  Duel_DrawCards(INACTIVE_DUELIST, 1, FALSE);
  Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE);

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
