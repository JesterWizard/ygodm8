#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "embodiment_of_apophis.h"

static u8 GetTurnRowForZone(struct DuelCard *zone) {
  u8 i;
  u8 j;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < MAX_ZONES_IN_ROW; j++) {
      if (gTurnZones[i][j] == zone)
        return i;
    }
  }

  return 0xFF;
}

static u8 ShouldBlockHarmfulEffectOnZone(struct DuelCard *zone) {
  u8 turnRow;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  turnRow = GetTurnRowForZone(zone);
  return IsImmuneToHarmfulTargetedEffectsOnField(zone->id, turnRow);
}

LYN_REPLACE_CHECK(ClearZoneAndSendMonToGraveyard);
void ClearZoneAndSendMonToGraveyard__Replacement(struct DuelCard *zone, u8 turn) {
  if (ShouldBlockHarmfulEffectOnZone(zone))
    return;

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER
      || EmbodimentOfApophisZoneIsMonsterForm(zone)
      || EmbodimentOfApophisZoneOnMonsterRow(zone))
    gTurnDuelistBattleState[turn]->graveyard = zone->id;
  ClearZone(zone);
}

LYN_REPLACE_CHECK(DecrementPermStage);
void DecrementPermStage__Replacement(struct DuelCard *zone) {
  if (ShouldBlockHarmfulEffectOnZone(zone))
    return;

  if (zone->permStage > -128)
    zone->permStage--;
}

LYN_REPLACE_CHECK(DecrementTempStage);
void DecrementTempStage__Replacement(struct DuelCard *zone) {
  if (ShouldBlockHarmfulEffectOnZone(zone))
    return;

  if (zone->tempStage > -128)
    zone->tempStage--;
}
