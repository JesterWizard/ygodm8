#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "world_suppression.h"
#include "duel_helpers.h"

#include "generated/field_spell_card_lookup_generated.inc"
#include "generated/field_spell_effect_table_generated.inc"
#include "generated/field_spell_mapping_generated.inc"

#define FIELD_SPELL_ZONE_ROW_INVALID 0xFF

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 turn);
void SetDuelFieldGfx(u8 field);
void ActivateCardEffectText(void);

static u8 GetFieldSpellZoneRow(void)
{
  return gSpellEffectData.row1;
}

static u8 GetFieldSpellZoneCol(void)
{
  return gSpellEffectData.col1;
}

u8 GetCustomFieldIdForSpellId(u8 spellId)
{
#if NUM_CUSTOM_FIELDS > 0
  if (spellId == CUSTOM_FIELD_SPELL_NONE || spellId >= NUM_CUSTOM_FIELD_SPELLS)
    return FIELD_ARENA;

  return sCustomFieldIdBySpellId[spellId - 1];
#else
  return FIELD_ARENA;
#endif
}

void ResetCustomFieldSpellState(void)
{
  gActiveCustomFieldSpellId = CUSTOM_FIELD_SPELL_NONE;
  gActiveFieldSpellZoneRow = FIELD_SPELL_ZONE_ROW_INVALID;
  gActiveFieldSpellZoneCol = FIELD_SPELL_ZONE_ROW_INVALID;
  gActiveFieldSpellController = FIELD_SPELL_CONTROLLER_NONE;
}

void RevertCustomFieldToArena(void)
{
  if (gActiveCustomFieldSpellId == CUSTOM_FIELD_SPELL_NONE)
    return;

  ResetCustomFieldSpellState();
  gDuel.field = FIELD_ARENA;

  if (!gHideEffectText)
    SetDuelFieldGfx(gDuel.field);
}

static u8 ZoneMatchesActiveFieldSpellZone(u8 row, u8 col)
{
  return gActiveCustomFieldSpellId != CUSTOM_FIELD_SPELL_NONE
      && gActiveFieldSpellZoneRow != FIELD_SPELL_ZONE_ROW_INVALID
      && gActiveFieldSpellZoneCol != FIELD_SPELL_ZONE_ROW_INVALID
      && gActiveFieldSpellZoneRow == row
      && gActiveFieldSpellZoneCol == col;
}

static u8 GetFixedRowForZone(struct DuelCard *zone)
{
  u8 i;
  u8 j;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < MAX_ZONES_IN_ROW; j++) {
      if (gFixedZones[i][j] == zone)
        return i;
    }
  }

  return FIELD_SPELL_ZONE_ROW_INVALID;
}

static u8 GetFixedColForZone(struct DuelCard *zone)
{
  u8 i;
  u8 j;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < MAX_ZONES_IN_ROW; j++) {
      if (gFixedZones[i][j] == zone)
        return j;
    }
  }

  return FIELD_SPELL_ZONE_ROW_INVALID;
}

static u8 CustomFieldSpellRemainsOnField(u8 customSpellId)
{
  return customSpellId == CUSTOM_FIELD_SPELL_SKYSCRAPER
      || customSpellId == CUSTOM_FIELD_SPELL_DIVINE_SANCTUARY;
}

static u8 ZoneStillHeldActiveCustomFieldSpell(struct DuelCard *zone, u8 row, u8 col)
{
#if NUM_CUSTOM_FIELDS == 0
  return FALSE;
#else
  if (zone == NULL || zone->id == CARD_NONE || gActiveCustomFieldSpellId == CUSTOM_FIELD_SPELL_NONE)
    return FALSE;

  if (!ZoneMatchesActiveFieldSpellZone(row, col))
    return FALSE;

  return LookupCustomFieldSpellIdForCard(zone->id) == gActiveCustomFieldSpellId;
#endif
}

void OnCustomFieldSpellZoneCleared(struct DuelCard *zone)
{
  u8 row;
  u8 col;

  if (gActiveCustomFieldSpellId == CUSTOM_FIELD_SPELL_NONE || zone == NULL)
    return;

  row = GetFixedRowForZone(zone);
  col = GetFixedColForZone(zone);

  if (ZoneStillHeldActiveCustomFieldSpell(zone, row, col))
    RevertCustomFieldToArena();
}

static u8 SpellEffectToFieldId(u8 spellEffect)
{
  if (spellEffect < SPELL_EFFECT_FOREST || spellEffect > SPELL_EFFECT_YAMI)
    return FIELD_ARENA;

  return (spellEffect - SPELL_EFFECT_FOREST) + FIELD_FOREST;
}

static struct DuelCard *FindFieldSpellZoneOnPlayerBackrow(u16 cardId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[PLAYER_BACKROW][col]->id == cardId)
      return gFixedZones[PLAYER_BACKROW][col];
  }

  return NULL;
}

static struct DuelCard *GetFieldSpellZone(void)
{
  u8 zoneRow = GetFieldSpellZoneRow();
  u8 zoneCol = GetFieldSpellZoneCol();
  struct DuelCard *zone;

  if (zoneCol >= MAX_ZONES_IN_ROW)
    return NULL;

  // ponytail: gTurnZones uses active-duelist POV; gFixedZones[ACTIVE_DUELIST_BACKROW]
  // is always player backrow, so opponent activations must resolve through gTurnZones.
  if (zoneRow < 5) {
    zone = gTurnZones[zoneRow][zoneCol];
    if (zone != NULL && zone->id == gSpellEffectData.id)
      return zone;
  }

  if (zoneRow <= PLAYER_HAND) {
    zone = gFixedZones[zoneRow][zoneCol];
    if (zone != NULL && zone->id == gSpellEffectData.id)
      return zone;
  }

  return FindFieldSpellZoneOnPlayerBackrow(gSpellEffectData.id);
}

static u8 RunFieldSpellActivation(u16 cardId, u8 fieldId, u8 customSpellId)
{
  struct DuelCard *zone = GetFieldSpellZone();

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  ResetCustomFieldSpellState();
  gDuel.field = fieldId;

  if (CustomFieldSpellRemainsOnField(customSpellId)) {
    gActiveFieldSpellZoneRow = GetFixedRowForZone(zone);
    gActiveFieldSpellZoneCol = GetFixedColForZone(zone);
    Duel_ActivateContinuousZone(zone);
  } else {
    // Match vanilla field spells: the activating card leaves its zone before the
    // terrain change is shown.
    ClearZoneAndSendMonToGraveyard(zone, ACTIVE_DUELIST);
  }

  if (customSpellId != CUSTOM_FIELD_SPELL_NONE) {
    gActiveCustomFieldSpellId = customSpellId;
    gActiveFieldSpellController = WhoseTurn();
  }

  if (!gHideEffectText) {
    SetDuelFieldGfx(gDuel.field);
    gCardEffectTextData.cardId = cardId;
    ActivateCardEffectText();
  }

  Duel_RefreshMonsterStatOverlays();
  return TRUE;
}

static u8 RunDefaultFieldSpellActivation(u8 spellId, u8 fieldId)
{
  return RunFieldSpellActivation(gSpellEffectData.id, fieldId, spellId);
}

u8 TryActivateVanillaFieldSpell(u16 cardId, u8 spellEffect)
{
  u8 fieldId;

  if (IsWorldSuppressionNegatingFieldSpell(cardId))
    return FALSE;

  SetCardInfo(cardId);
  fieldId = SpellEffectToFieldId(gCardInfo.spellEffect);

  if (fieldId == FIELD_ARENA)
    return FALSE;

  return RunFieldSpellActivation(cardId, fieldId, CUSTOM_FIELD_SPELL_NONE);
}

void ActivateCustomFieldSpell(u8 spellId)
{
  RunDefaultFieldSpellActivation(spellId, GetCustomFieldIdForSpellId(spellId));
}

u8 TryActivateCustomFieldSpell(u16 cardId)
{
  u8 spellId;

#if NUM_CUSTOM_FIELDS == 0
  return FALSE;
#else
  spellId = LookupCustomFieldSpellIdForCard(cardId);
  if (spellId == CUSTOM_FIELD_SPELL_NONE)
    return FALSE;

  if (IsWorldSuppressionNegatingFieldSpell(cardId))
    return FALSE;

  sCustomFieldSpellEffects[spellId - 1]();
  return TRUE;
#endif
}

void OnFieldSpellEndTurn(void)
{
}

void OnFieldSpellZoneCleared(struct DuelCard *zone)
{
  OnCustomFieldSpellZoneCleared(zone);
}
