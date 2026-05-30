#include "global.h"
#include "common-chax.h"
#include "dynamic_equip.h"

void UpdateDuelGfxExceptField(void);

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 IsMonsterCard(u16 cardId)
{
  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 GetFixedRowForZone(const struct DuelCard *zone, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = 0; row < PLAYER_BACKROW + 1; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col] == zone) {
        *outCol = col;
        return row;
      }
    }
  }

  return DYNAMIC_EQUIP_COORD_INVALID;
}

static u8 GetFixedCoordsForZone(const struct DuelCard *zone, u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = GetFixedRowForZone(zone, &col);

  *outRow = row;
  *outCol = col;
  return row != DYNAMIC_EQUIP_COORD_INVALID;
}

static struct DuelCard *GetZoneFromFixedCoords(u8 row, u8 col)
{
  if (row == DYNAMIC_EQUIP_COORD_INVALID || col >= MAX_ZONES_IN_ROW)
    return NULL;

  return gFixedZones[row][col];
}

u8 GetDuelistForZone(const struct DuelCard *zone)
{
  u8 col;
  u8 fixedRow = GetFixedRowForZone(zone, &col);

  if (fixedRow == DYNAMIC_EQUIP_COORD_INVALID)
    return 0xFF;

  if (fixedRow == OPPONENT_BACKROW || fixedRow == OPPONENT_MONSTER_ROW)
    return DUEL_OPPONENT;

  return DUEL_PLAYER;
}

u8 CountDuelistSpellTrapBackrowCards(u8 duelist)
{
  u8 backrowRow = duelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 id = gFixedZones[backrowRow][i]->id;

    if (id == CARD_NONE)
      continue;

    if (IsSpellOrTrapCard(id))
      count++;
  }

  return count;
}

u8 CountDuelistMonsterRowCards(u8 duelist)
{
  u8 monsterRow = duelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[monsterRow][i]->id != CARD_NONE)
      count++;
  }

  return count;
}

static u8 CountStagesForSpell(u16 spellId, u8 duelist)
{
  u8 count;

  if (spellId == MAGE_POWER)
    count = CountDuelistSpellTrapBackrowCards(duelist);
  else if (spellId == UNITED_WE_STAND)
    count = CountDuelistMonsterRowCards(duelist);
  else
    return 0;

  if (count > MAX_ZONES_IN_ROW)
    count = MAX_ZONES_IN_ROW;

  return count;
}

static void ClearDynamicEquipLink(struct DynamicEquipLink *link)
{
  link->active = FALSE;
  link->spellFixedRow = DYNAMIC_EQUIP_COORD_INVALID;
  link->spellFixedCol = DYNAMIC_EQUIP_COORD_INVALID;
  link->targetFixedRow = DYNAMIC_EQUIP_COORD_INVALID;
  link->targetFixedCol = DYNAMIC_EQUIP_COORD_INVALID;
  link->spellId = CARD_NONE;
  link->appliedStages = 0;
}

void ResetDynamicEquips(void)
{
  u8 i;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++)
    ClearDynamicEquipLink(&gDynamicEquipLinks[i]);
}

void ApplyDynamicEquipStages(struct DuelCard *targetZone, u8 stages)
{
  while (stages--)
    IncrementPermStage(targetZone);
}

void RemoveDynamicEquipStages(struct DynamicEquipLink *link)
{
  struct DuelCard *targetZone;
  u8 stages = link->appliedStages;

  targetZone = GetZoneFromFixedCoords(link->targetFixedRow, link->targetFixedCol);

  if (targetZone == NULL || link->appliedStages == 0)
    return;

  while (stages--)
    DecrementPermStage(targetZone);

  link->appliedStages = 0;
}

static struct DynamicEquipLink *FindInactiveDynamicEquipSlot(void)
{
  u8 i;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    if (!gDynamicEquipLinks[i].active)
      return &gDynamicEquipLinks[i];
  }

  return NULL;
}

static struct DynamicEquipLink *FindDynamicEquipSlot(void)
{
  u8 i;
  struct DynamicEquipLink *slot = FindInactiveDynamicEquipSlot();

  if (slot != NULL)
    return slot;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    struct DuelCard *spellZone = GetZoneFromFixedCoords(
        gDynamicEquipLinks[i].spellFixedRow, gDynamicEquipLinks[i].spellFixedCol);

    if (!gDynamicEquipLinks[i].active || !IsActiveDynamicEquipSpellZone(spellZone)) {
      RemoveDynamicEquipStages(&gDynamicEquipLinks[i]);
      ClearDynamicEquipLink(&gDynamicEquipLinks[i]);
      return &gDynamicEquipLinks[i];
    }
  }

  RemoveDynamicEquipStages(&gDynamicEquipLinks[0]);
  ClearDynamicEquipLink(&gDynamicEquipLinks[0]);
  return &gDynamicEquipLinks[0];
}

u8 RegisterDynamicEquip(struct DuelCard *spellZone, struct DuelCard *targetZone, u16 spellId, u8 stages)
{
  struct DynamicEquipLink *link = FindDynamicEquipSlot();
  u8 spellRow;
  u8 spellCol;
  u8 targetRow;
  u8 targetCol;

  if (link == NULL
      || !GetFixedCoordsForZone(spellZone, &spellRow, &spellCol)
      || !GetFixedCoordsForZone(targetZone, &targetRow, &targetCol))
    return FALSE;

  link->active = TRUE;
  link->spellFixedRow = spellRow;
  link->spellFixedCol = spellCol;
  link->targetFixedRow = targetRow;
  link->targetFixedCol = targetCol;
  link->spellId = spellId;
  link->appliedStages = stages;
  return TRUE;
}

static struct DynamicEquipLink *FindDynamicEquipForSpellCoords(u8 row, u8 col)
{
  u8 i;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    if (gDynamicEquipLinks[i].active
        && gDynamicEquipLinks[i].spellFixedRow == row
        && gDynamicEquipLinks[i].spellFixedCol == col)
      return &gDynamicEquipLinks[i];
  }

  return NULL;
}

static struct DynamicEquipLink *FindDynamicEquipForTargetCoords(u8 row, u8 col)
{
  u8 i;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    if (gDynamicEquipLinks[i].active
        && gDynamicEquipLinks[i].targetFixedRow == row
        && gDynamicEquipLinks[i].targetFixedCol == col)
      return &gDynamicEquipLinks[i];
  }

  return NULL;
}

static struct DynamicEquipLink *FindDynamicEquipForSpellZone(const struct DuelCard *zone)
{
  u8 row;
  u8 col;

  if (!GetFixedCoordsForZone(zone, &row, &col))
    return NULL;

  return FindDynamicEquipForSpellCoords(row, col);
}

static struct DynamicEquipLink *FindDynamicEquipForTargetZone(const struct DuelCard *zone)
{
  u8 row;
  u8 col;

  if (!GetFixedCoordsForZone(zone, &row, &col))
    return NULL;

  return FindDynamicEquipForTargetCoords(row, col);
}

static u8 RecalculateDynamicEquip(struct DynamicEquipLink *link)
{
  struct DuelCard *spellZone;
  struct DuelCard *targetZone;
  u8 duelist;
  u8 newStages;
  s8 delta;
  u8 i;

  if (!link->active)
    return FALSE;

  spellZone = GetZoneFromFixedCoords(link->spellFixedRow, link->spellFixedCol);
  targetZone = GetZoneFromFixedCoords(link->targetFixedRow, link->targetFixedCol);

  if (spellZone == NULL || targetZone == NULL
      || !IsActiveDynamicEquipSpellZone(spellZone)
      || spellZone->id != link->spellId
      || targetZone->id == CARD_NONE
      || !IsMonsterCard(targetZone->id)) {
    RemoveDynamicEquipStages(link);
    ClearDynamicEquipLink(link);
    return TRUE;
  }

  duelist = GetDuelistForZone(spellZone);
  if (duelist == 0xFF) {
    RemoveDynamicEquipStages(link);
    ClearDynamicEquipLink(link);
    return TRUE;
  }

  newStages = CountStagesForSpell(link->spellId, duelist);
  delta = newStages - link->appliedStages;

  if (delta == 0)
    return FALSE;

  if (delta > 0) {
    for (i = 0; i < delta; i++)
      IncrementPermStage(targetZone);
  } else {
    for (i = 0; i < -delta; i++)
      DecrementPermStage(targetZone);
  }

  link->appliedStages = newStages;
  return TRUE;
}

void RecalculateAllDynamicEquips(void)
{
  u8 i;
  u8 changed = FALSE;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    if (RecalculateDynamicEquip(&gDynamicEquipLinks[i]))
      changed = TRUE;
  }

  if (changed)
    NotifyDynamicEquipFieldChanged();
}

s8 GetDynamicEquipStageDelta(const struct DuelCard *zone)
{
  u8 i;
  u8 row;
  u8 col;
  s8 delta = 0;

  if (!GetFixedCoordsForZone(zone, &row, &col))
    return 0;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    struct DynamicEquipLink *link = &gDynamicEquipLinks[i];
    struct DuelCard *spellZone;
    u8 duelist;
    u8 liveStages;

    if (!link->active)
      continue;

    if (link->targetFixedRow != row || link->targetFixedCol != col)
      continue;

    spellZone = GetZoneFromFixedCoords(link->spellFixedRow, link->spellFixedCol);
    if (!IsActiveDynamicEquipSpellZone(spellZone))
      continue;

    duelist = GetDuelistForZone(spellZone);
    if (duelist == 0xFF)
      continue;

    liveStages = CountStagesForSpell(link->spellId, duelist);
    delta += liveStages - link->appliedStages;
  }

  return delta;
}

u8 HasActiveDynamicEquips(void)
{
  u8 i;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    if (gDynamicEquipLinks[i].active)
      return TRUE;
  }

  return FALSE;
}

u8 IsActiveDynamicEquipSpellZone(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  switch (zone->id) {
    case MAGE_POWER:
    case UNITED_WE_STAND:
      return zone->isFaceUp == TRUE && zone->isLocked == TRUE;
    default:
      return FALSE;
  }
}

static u8 FieldHasActiveDynamicEquipSpell(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsActiveDynamicEquipSpellZone(gFixedZones[row][col]))
        return TRUE;
    }
  }

  return FALSE;
}

void NotifyDynamicEquipFieldChanged(void)
{
  if (!gHideEffectText && FieldHasActiveDynamicEquipSpell())
    UpdateDuelGfxExceptField();
}

void OnDynamicEquipZoneAboutToClear(struct DuelCard *zone)
{
  struct DynamicEquipLink *link;
  struct DuelCard *spellZone;

  link = FindDynamicEquipForSpellZone(zone);
  if (link != NULL) {
    RemoveDynamicEquipStages(link);
    ClearDynamicEquipLink(link);
    return;
  }

  link = FindDynamicEquipForTargetZone(zone);
  if (link != NULL) {
    u16 spellId = link->spellId;

    spellZone = GetZoneFromFixedCoords(link->spellFixedRow, link->spellFixedCol);
    RemoveDynamicEquipStages(link);
    ClearDynamicEquipLink(link);

    if (spellZone != NULL && spellZone->id == spellId)
      ClearZone(spellZone);
  }
}
