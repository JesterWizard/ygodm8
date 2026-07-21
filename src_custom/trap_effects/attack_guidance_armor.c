#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectATTACK_GUIDANCE_ARMOR(void)
{
  struct DuelCard *attacker;

  Duel_ShowTrapResponseText(ATTACK_GUIDANCE_ARMOR, gTrapEffectData.originCardId);

  attacker = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
  if (attacker != NULL && GetTypeGroup(attacker->id) == TYPE_GROUP_MONSTER)
    Duel_DestroyZone(attacker, ACTIVE_DUELIST, FALSE);

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
