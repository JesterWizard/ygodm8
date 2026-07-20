#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectACE_OF_WAND(void)
{
  u16 atk = 0;
  u8 heads;

  Duel_ShowTrapResponseText(ACE_OF_WAND, gTrapEffectData.originCardId);

  if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER) {
    SetCardInfo(gTrapEffectData.originCardId);
    atk = gCardInfo.atk;
  }

  heads = RandRangeU8(0, 1);
  if (atk > 0) {
    if (heads)
      Duel_ChangeLp(ACTIVE_DUELIST, (s32)atk, TRUE);
    else
      Duel_ChangeLp(ACTIVE_DUELIST, -(s32)atk, TRUE);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();

  /* ponytail: needs destroy-by-effect trigger wire + trapEffect ID. */
}
