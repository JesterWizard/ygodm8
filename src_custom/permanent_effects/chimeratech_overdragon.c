#include "global.h"
#include "common-chax.h"
#include "chimeratech_overdragon.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "fusion_recipes.h"
#include "the_dark_door.h"

void UpdateDuelGfxExceptField(void);

#define OVERDRAGON_STAT_PER_MATERIAL 800
#define OVERDRAGON_CELL_NONE 0xFF

extern u8 gChimeratechOverdragonMaterialCount[];
extern u8 gChimeratechOverdragonAttacksUsed[];

static u8 FixedMonsterCellIndex(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return (MAX_ZONES_IN_ROW - 1) - fixedCol;
  if (fixedRow == PLAYER_MONSTER_ROW)
    return MAX_ZONES_IN_ROW + fixedCol;
  return OVERDRAGON_CELL_NONE;
}

static u8 GetFixedCellIndexForZone(struct DuelCard *zone, u8 *cellIndex)
{
  u8 fixedRow;
  u8 fixedCol;

  if (Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol) == FALSE)
    return FALSE;

  *cellIndex = FixedMonsterCellIndex(fixedRow, fixedCol);
  return *cellIndex != OVERDRAGON_CELL_NONE;
}

static u8 MaterialCountForZone(struct DuelCard *zone)
{
  u8 cellIndex;

  if (zone == NULL || zone->id != CHIMERATECH_OVERDRAGON)
    return 0;

  if (!GetFixedCellIndexForZone(zone, &cellIndex))
    return 0;

  return gChimeratechOverdragonMaterialCount[cellIndex];
}

u16 ChimeratechOverdragon_EstimateAtk(u8 materialCount)
{
  u32 atk;

  if (materialCount < 2)
    materialCount = 2;

  atk = (u32)materialCount * OVERDRAGON_STAT_PER_MATERIAL;
  if (atk > 65535)
    atk = 65535;

  return (u16)atk;
}

u8 ChimeratechOverdragon_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 mats;
  u16 stat;

  if (zone == NULL || zone->id != CHIMERATECH_OVERDRAGON)
    return FALSE;

  mats = MaterialCountForZone(zone);
  if (mats < 2)
    mats = 2;

  stat = ChimeratechOverdragon_EstimateAtk(mats);
  Duel_WriteCardInfoStats(zone->id, stat, stat);
  return TRUE;
}

void ClearChimeratechOverdragonBoardStatsForZone(struct DuelCard *zone)
{
  u8 cellIndex;

  if (!GetFixedCellIndexForZone(zone, &cellIndex))
    return;

  gChimeratechOverdragonMaterialCount[cellIndex] = 0;
  gChimeratechOverdragonAttacksUsed[cellIndex] = 0;
}

void ClearChimeratechOverdragonAttacksUsed(void)
{
  u8 i;

  for (i = 0; i < 10; i++)
    gChimeratechOverdragonAttacksUsed[i] = 0;
}

void ClearChimeratechOverdragonState(void)
{
  u8 i;

  for (i = 0; i < 10; i++) {
    gChimeratechOverdragonMaterialCount[i] = 0;
    gChimeratechOverdragonAttacksUsed[i] = 0;
  }
}

static struct DuelCard *FindActiveOverdragonZone(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == CHIMERATECH_OVERDRAGON)
      return zone;
  }

  return NULL;
}

/* TCG: send all other cards you control (field only — never hand). */
static void SendAllOtherCardsYouControlToGy(struct DuelCard *protectedZone)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == protectedZone || zone == NULL || zone->id == CARD_NONE)
      continue;
    if (Duel_ZoneIsHandSlot(zone))
      continue;

    if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (Duel_ZoneIsHandSlot(zone))
      continue;

    if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

void ChimeratechOverdragon_OnFusionSummoned(u8 materialCount)
{
  struct DuelCard *zone;
  u8 cellIndex;

  zone = FindActiveOverdragonZone();
  if (zone == NULL)
    return;

  if (materialCount < 2)
    materialCount = 2;
  if (materialCount > FUSION_MAX_MATERIALS)
    materialCount = FUSION_MAX_MATERIALS;

  if (GetFixedCellIndexForZone(zone, &cellIndex)) {
    gChimeratechOverdragonMaterialCount[cellIndex] = materialCount;
    gChimeratechOverdragonAttacksUsed[cellIndex] = 0;
  }

  zone->isFaceUp = TRUE;
  zone->isDefending = FALSE;

  Duel_ShowCardEffectText(CHIMERATECH_OVERDRAGON,
                          CARD_EFFECT_TEXT_CHIMERATECH_OVERDRAGON_POPUP_1);
  if (IsDuelOver() == TRUE)
    return;

  SendAllOtherCardsYouControlToGy(zone);
  if (IsDuelOver() == TRUE)
    return;

  UpdateDuelGfxExceptField();
}

void TryUnlockChimeratechOverdragonForNextAttack(struct DuelCard *attacker)
{
  u8 cellIndex;
  u8 mats;
  u8 used;

  if (attacker == NULL || attacker->id != CHIMERATECH_OVERDRAGON)
    return;

  if (IsTheDarkDoorActiveOnField())
    return;

  if (!GetFixedCellIndexForZone(attacker, &cellIndex))
    return;

  mats = gChimeratechOverdragonMaterialCount[cellIndex];
  if (mats < 2)
    return;

  used = gChimeratechOverdragonAttacksUsed[cellIndex];
  if (used >= mats)
    return;

  used++;
  gChimeratechOverdragonAttacksUsed[cellIndex] = used;

  if (used < mats)
    attacker->isLocked = FALSE;
}

u8 ChimeratechOverdragon_BlocksDirectAttack(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == CHIMERATECH_OVERDRAGON;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ChimeratechOverdragon_SelfCheck(void)
{
  if (ChimeratechOverdragon_EstimateAtk(2) != 1600)
    while (1)
      ;

  if (ChimeratechOverdragon_EstimateAtk(4) != 3200)
    while (1)
      ;
}
#endif
