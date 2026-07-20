#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

void UpdateDuelGfxExceptField(void);

/* 1 stage ~= 500 ATK; printed +400 → nearest 1 stage. */
#define TYRANT_WING_ATK_STAGES 1

APPEND_TEXT void EffectTYRANT_WING(void)
{
  u8 col;
  u8 row;
  struct DuelCard *dragon = NULL;
  struct DuelCard *trapZone;

  Duel_ShowTrapResponseText(TYRANT_WING, gTrapEffectData.originCardId);

  /* Prefer own field Dragon; else any Dragon on field. */
  row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && Duel_CardHasMonsterType(zone->id, TYPE_DRAGON)) {
      dragon = zone;
      break;
    }
  }

  if (dragon == NULL) {
    row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && Duel_CardHasMonsterType(zone->id, TYPE_DRAGON)) {
        dragon = zone;
        break;
      }
    }
  }

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (dragon != NULL && trapZone != NULL) {
    ApplyDynamicEquipStages(dragon, TYRANT_WING_ATK_STAGES);
    RegisterDynamicEquip(trapZone, dragon, TYRANT_WING, TYRANT_WING_ATK_STAGES);
    Duel_ActivateContinuousZone(trapZone);
    NotifyDynamicEquipFieldChanged();
  } else if (trapZone != NULL) {
    Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
  }

  UpdateDuelGfxExceptField();

  /* ponytail: second attack on monsters + End Phase self-destroy after attack
   * need battle/turn hooks. Ceiling: Dragon equip + ~500 ATK stage. */
}
