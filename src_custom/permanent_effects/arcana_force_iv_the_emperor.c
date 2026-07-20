#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static const char sArcanaForceName[] APPEND_RODATA = "Arcana Force";

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

static u8 SummonerFixedMonsterRow(void)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone(SelfZone(), &fixedRow, &col))
    return PLAYER_MONSTER_ROW;

  return fixedRow;
}

static u8 IsArcanaForceMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sArcanaForceName);
}

static void ApplyCoinToArcanaForceMonsters(u8 heads)
{
  u8 fixedRow = SummonerFixedMonsterRow();
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (!IsArcanaForceMonster(zone->id))
      continue;

    if (heads)
      IncrementTempStage(zone);
    else
      DecrementTempStage(zone);
  }
}

unsigned char ShouldActivateARCANA_FORCE_IV_THE_EMPEROR(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ARCANA_FORCE_IV_THE_EMPEROR)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return TRUE;
}

void ActivateARCANA_FORCE_IV_THE_EMPEROR(void)
{
  struct DuelCard *zone;
  u8 heads;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_IV_THE_EMPEROR, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  zone->unk4 = 1;
  heads = RandRangeU8(0, 1) == 1;
  ApplyCoinToArcanaForceMonsters(heads);
  /* ponytail: ±500 ATK uses tempStage (~500/stage); only your Arcana Force on field. */
}
