#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "embodiment_of_apophis.h"
#include "expanded_graveyard.h"
#include "graveyard_effects.h"
#include "executor_makyura.h"
#include "elemental_hero_absolute_zero.h"
#include "elemental_hero_core.h"
#include "ojama_trio.h"
#include "the_despair_uranus.h"
#include "archlord_kristya.h"

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

  if (Duel_IsMonsterEffectResolving() && !Duel_IsSpellEffectResolving()
      && gMonEffect.id != CARD_NONE
      && GetTypeGroup(gMonEffect.id) == TYPE_GROUP_MONSTER
      && Duel_TryNegateMonsterEffectOnZone(gMonEffect.id, zone))
    return TRUE;

  if (IsTheDespairUranusProtectingZoneFromEffectDestroy(zone))
    return TRUE;

  return FALSE;
}

LYN_REPLACE_CHECK(ClearZoneAndSendMonToGraveyard);
void ClearZoneAndSendMonToGraveyard__Replacement(struct DuelCard *zone, u8 turn) {
  if (ShouldBlockEffectOnZone(zone))
    return;

  ApplyOjamaTrioDestructionDamage(zone);

  if (ArchlordKristya_TrySendFaceUpFieldToDeckTop(zone, turn)) {
    ClearZone(zone);
    return;
  }

  if (zone->id != CARD_NONE) {
    if (Duel_CardIsMonster(zone->id)
        || EmbodimentOfApophisZoneIsMonsterForm(zone)
        || EmbodimentOfApophisZoneOnMonsterRow(zone)
        || OjamaTrioZoneIsMonsterForm(zone))
      NoteGraveyardMonsterSend(zone);
    GraveyardExpand_PushTurn(turn, zone->id);
    TryArmExecutorMakyuraOnGraveyardSend(turn, zone->id);
    if (Duel_ZoneIsHandSlot(zone) && zone->id == ELEMENTAL_HERO_ABSOLUTE_ZERO)
      MarkAbsoluteZeroHandGraveyardClear();
    /* Hand sends skip NoteGraveyardMonsterSend for non-monsters; always clear Core arm. */
    ClearElementalHeroCoreReviveIfHandSend(zone);
  }
  ClearZone(zone);
  TryShowPendingExecutorMakyuraPopup();
}

LYN_REPLACE_CHECK(DecrementPermStage);
void DecrementPermStage__Replacement(struct DuelCard *zone) {
  if (ShouldBlockHarmfulEffectOnZone(zone))
    return;

  if (Duel_IsSpellEffectResolving() && Duel_ZoneIsImmuneToSpellEffects(zone))
    return;

  if (zone->permStage > -128)
    zone->permStage--;
}

LYN_REPLACE_CHECK(DecrementTempStage);
void DecrementTempStage__Replacement(struct DuelCard *zone) {
  if (ShouldBlockHarmfulEffectOnZone(zone))
    return;

  if (Duel_IsSpellEffectResolving() && Duel_ZoneIsImmuneToSpellEffects(zone))
    return;

  if (zone->tempStage > -128)
    zone->tempStage--;
}

LYN_REPLACE_CHECK(IncrementPermStage);
void IncrementPermStage__Replacement(struct DuelCard *zone) {
  if (zone->permStage < 127)
    zone->permStage++;
}
