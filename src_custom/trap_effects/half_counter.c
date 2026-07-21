#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void IncrementPermStage(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectHALF_COUNTER(void)
{
  struct DuelCard *defender;
  struct DuelCard *attacker;
  u16 halfAtk;
  u8 stages;
  u8 i;

  Duel_ShowTrapResponseText(HALF_COUNTER, gTrapEffectData.originCardId);

  defender = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][0];
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone != NULL && zone->id != CARD_NONE) {
      defender = zone;
      break;
    }
  }

  attacker = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
  if (defender != NULL && attacker != NULL
      && GetTypeGroup(attacker->id) == TYPE_GROUP_MONSTER) {
    SetCardInfo(attacker->id);
    halfAtk = gCardInfo.atk / 2;
    stages = (u8)(halfAtk / 500);
    for (i = 0; i < stages; i++)
      IncrementPermStage(defender);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
