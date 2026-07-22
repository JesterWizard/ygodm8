#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "shatiel.h"

extern void UpdateDuelGfxExceptField(void);

#define SHATIEL_FAIRY_STAT_PER_MONSTER 400

static u8 IsActiveFaceUpShatiel(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != SHATIEL)
    return FALSE;

  if (IsCardFaceUp((struct DuelCard *)zone))
    return TRUE;

  /* Attack-position summons stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 RowHasActiveShatiel(u8 fixedMonsterRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsActiveFaceUpShatiel(gFixedZones[fixedMonsterRow][col]))
      return TRUE;
  }

  return FALSE;
}

static u8 CountFairiesOnMonsterRow(u8 fixedMonsterRow)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *rowZone = gFixedZones[fixedMonsterRow][col];
    u16 cardId;

    if (rowZone == NULL || rowZone->id == CARD_NONE)
      continue;

    cardId = rowZone->id;
    if (cardId >= NUM_TOTAL_CARDS)
      continue;

    /* gCardData_NEW type check — avoids GetTypeGroup clobbering gCardInfo. */
    if (gCardData_NEW[cardId].type != TYPE_FAIRY)
      continue;

    if (cardId == SHATIEL)
      continue;

    count++;
  }

  return count;
}

void ApplyShatielFairyStatBoost(const struct DuelCard *zone)
{
  u8 row;
  u8 col;
  u8 fairyCount;
  u32 atk;
  u32 def;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (gCardInfo.id != zone->id || gCardInfo.type >= TYPE_SPELL)
    return;

  if (gCardInfo.type != TYPE_FAIRY)
    return;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 zoneOnRow = FALSE;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col] == zone)
        zoneOnRow = TRUE;
    }

    if (!zoneOnRow || !RowHasActiveShatiel(row))
      continue;

    fairyCount = CountFairiesOnMonsterRow(row);
    if (fairyCount == 0)
      return;

    atk = (u32)gCardInfo.atk + (u32)fairyCount * SHATIEL_FAIRY_STAT_PER_MONSTER;
    def = (u32)gCardInfo.def + (u32)fairyCount * SHATIEL_FAIRY_STAT_PER_MONSTER;
    gCardInfo.atk = Duel_ClampStat(atk);
    gCardInfo.def = Duel_ClampStat(def);
    return;
  }
}

void Shatiel_OnZoneCleared(const struct DuelCard *zone)
{
  if (zone != NULL && zone->id == SHATIEL)
    UpdateDuelGfxExceptField();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void Shatiel_SelfCheck(void)
{
  if (SHATIEL_FAIRY_STAT_PER_MONSTER != 400)
    while (1)
      ;
}
#endif
