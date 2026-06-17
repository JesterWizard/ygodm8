#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "duel_helpers.h"
#include "embodiment_of_apophis.h"
#include "graveyard_effects.h"
#include "ojama_trio.h"

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

static u8 ShouldBlockEffectOnZone(struct DuelCard *zone) {
  if (ShouldBlockHarmfulEffectOnZone(zone))
    return TRUE;

  if (Duel_IsSpellEffectResolving() && Duel_ZoneIsImmuneToSpellEffects(zone))
    return TRUE;

  return FALSE;
}

LYN_REPLACE_CHECK(ClearZoneAndSendMonToGraveyard);
void ClearZoneAndSendMonToGraveyard__Replacement(struct DuelCard *zone, u8 turn) {
  if (ShouldBlockEffectOnZone(zone))
    return;

  ApplyOjamaTrioDestructionDamage(zone);

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER
      || EmbodimentOfApophisZoneIsMonsterForm(zone)
      || EmbodimentOfApophisZoneOnMonsterRow(zone)
      || OjamaTrioZoneIsMonsterForm(zone)) {
    NoteGraveyardMonsterSend(zone);
    gTurnDuelistBattleState[turn]->graveyard = zone->id;
  }
  ClearZone(zone);
}

LYN_REPLACE_CHECK(DecrementPermStage);
void DecrementPermStage__Replacement(struct DuelCard *zone) {
  if (ShouldBlockEffectOnZone(zone))
    return;

  if (zone->permStage > -128)
    zone->permStage--;
}

LYN_REPLACE_CHECK(DecrementTempStage);
void DecrementTempStage__Replacement(struct DuelCard *zone) {
  if (ShouldBlockEffectOnZone(zone))
    return;

  if (zone->tempStage > -128)
    zone->tempStage--;
}

LYN_REPLACE_CHECK(IncrementPermStage);
void IncrementPermStage__Replacement(struct DuelCard *zone) {
  if (ShouldBlockEffectOnZone(zone))
    return;

  if (zone->permStage < 127)
    zone->permStage++;
}
