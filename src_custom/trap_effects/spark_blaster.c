#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectSPARK_BLASTER(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  struct DuelCard *sparkman = NULL;
  struct DuelCard *trapZone;

  Duel_ShowTrapResponseText(SPARK_BLASTER, gTrapEffectData.originCardId);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id == ELEMENTAL_HERO_SPARKMAN) {
      sparkman = zone;
      break;
    }
  }

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (sparkman != NULL && trapZone != NULL) {
    RegisterDynamicEquip(trapZone, sparkman, SPARK_BLASTER, 0);
    Duel_ActivateContinuousZone(trapZone);
    trapZone->unk4 = 0;
    NotifyDynamicEquipFieldChanged();
  } else if (trapZone != NULL) {
    Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
  }

  UpdateDuelGfxExceptField();

}
