#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "card.h"
#include "mirror_wall.h"
#include "royal_decree.h"

#define MIRROR_WALL_LP_COST 2000

struct MirrorWallActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct MirrorWallActionData sActionData;

static u16 GetDuelBoardCellIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone < base || zone >= base + MAX_DUEL_BOARD_CELLS)
    return 0xFFFF;

  return (u16)(zone - base);
}

static u8 MirrorWallZoneIsHalved(const struct DuelCard *zone)
{
  u16 index = GetDuelBoardCellIndex(zone);

  if (index >= MAX_DUEL_BOARD_CELLS)
    return FALSE;

  return gMirrorWallHalvedMask[index] != 0;
}

static void MarkMirrorWallHalvedZone(struct DuelCard *zone)
{
  u16 index = GetDuelBoardCellIndex(zone);

  if (index >= MAX_DUEL_BOARD_CELLS)
    return;

  gMirrorWallHalvedMask[index] = 1;
}

static struct DuelCard *FindMirrorWallOnDefenderBackrow(void)
{
  u8 i;
  u8 backrow = (WhoseTurn() == DUEL_PLAYER) ? OPPONENT_BACKROW : PLAYER_BACKROW;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[backrow][i];
    if (zone->id == MIRROR_WALL)
      return zone;
  }

  return NULL;
}

static u8 IsMonsterAttackAction(void)
{
  return sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 4
      || sActionData.id == 5 || sActionData.id == 6;
}

static u16 *GetActiveAttackerAtkField(u16 *attackerCardId)
{
  if (WhoseTurn() == DUEL_PLAYER) {
    if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4)
      return NULL;

    *attackerCardId = sActionData.playerCardId;
    return &sActionData.playerCardAtkOrLifePointsMod;
  }

  if (sActionData.id != 1 && sActionData.id != 5 && sActionData.id != 6)
    return NULL;

  *attackerCardId = sActionData.opponentCardId;
  return &sActionData.opponentCardAtkOrLifePointsMod;
}

static struct DuelCard *GetActiveAttackerZone(void)
{
  if (WhoseTurn() == DUEL_PLAYER) {
    if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4)
      return NULL;

    return gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
  }

  if (sActionData.id != 1 && sActionData.id != 5 && sActionData.id != 6)
    return NULL;

  return gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
}

static u8 ActiveDuelistCanPayMirrorWallCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= MIRROR_WALL_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= MIRROR_WALL_LP_COST;
}

u8 IsActivatedMirrorWallZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == MIRROR_WALL && zone->isFaceUp == TRUE;
}

u8 IsMirrorWallActiveOnField(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id == MIRROR_WALL && zone->isFaceUp == TRUE
          && !IsRoyalDecreeNegatingTrap(MIRROR_WALL))
        return TRUE;
    }
  }

  return FALSE;
}

void MarkMirrorWallJustSet(struct DuelCard *zone)
{
  if (zone->id == MIRROR_WALL)
    zone->unk4 = 1;
}

void AgeMirrorWallSetFlags(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[PLAYER_BACKROW][i];
    if (zone->id == MIRROR_WALL && zone->unk4 != 0)
      zone->unk4 = 0;
    zone = gFixedZones[OPPONENT_BACKROW][i];
    if (zone->id == MIRROR_WALL && zone->unk4 != 0)
      zone->unk4 = 0;
  }
}

unsigned char ShouldActivateMirrorWallUpkeep(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_BACKROW)
    return FALSE;
  if (gActiveEffect.col != GetFirstCardMatchZoneId(gTurnZones[ACTIVE_DUELIST_BACKROW], MIRROR_WALL))
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->id == MIRROR_WALL && zone->isFaceUp == TRUE;
}

void ActivateMirrorWallUpkeep(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  if (ActiveDuelistCanPayMirrorWallCost()) {
    Duel_ChangeLp(ACTIVE_DUELIST, -MIRROR_WALL_LP_COST, TRUE);
    return;
  }

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  ClearMirrorWallHalvedMask();
  Duel_ShowEffectTextTyped(MIRROR_WALL, 9);
}

void ApplyMirrorWallAtkHalving(const struct DuelCard *zone)
{
  u16 index = GetDuelBoardCellIndex(zone);

  if (index >= MAX_DUEL_BOARD_CELLS || gMirrorWallHalvedMask[index] == 0)
    return;

  if (!IsMirrorWallActiveOnField())
    return;

  gCardInfo.atk = (u16)(gCardInfo.atk / 2);
}

void ClearMirrorWallHalvedZone(const struct DuelCard *zone)
{
  u16 index = GetDuelBoardCellIndex(zone);

  if (index >= MAX_DUEL_BOARD_CELLS)
    return;

  gMirrorWallHalvedMask[index] = 0;
}

void ClearMirrorWallHalvedMask(void)
{
  u16 i;

  for (i = 0; i < MAX_DUEL_BOARD_CELLS; i++)
    gMirrorWallHalvedMask[i] = 0;
}

void MirrorWall_OnZoneCleared(const struct DuelCard *zone)
{
  if (zone == NULL)
    return;

  if (zone->id == MIRROR_WALL)
    ClearMirrorWallHalvedMask();
  else if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
    ClearMirrorWallHalvedZone(zone);
}

void TryApplyMirrorWallToPendingAction(void)
{
  u16 *attackerAtk;
  u16 attackerCardId;
  struct DuelCard *attackerZone;
  struct DuelCard *mirrorWall;

  RefreshPendingBattleActionStatsFromZones();

  if (!IsMonsterAttackAction())
    return;

  mirrorWall = FindMirrorWallOnDefenderBackrow();
  if (mirrorWall == NULL || mirrorWall->unk4 != 0)
    return;

  if (IsRoyalDecreeNegatingTrap(MIRROR_WALL))
    return;

  attackerAtk = GetActiveAttackerAtkField(&attackerCardId);
  attackerZone = GetActiveAttackerZone();
  if (attackerAtk == NULL || attackerZone == NULL || attackerCardId == CARD_NONE)
    return;

  if (!mirrorWall->isFaceUp)
    Duel_ActivateContinuousZone(mirrorWall);

  if (!MirrorWallZoneIsHalved(attackerZone)) {
    *attackerAtk = (u16)(*attackerAtk / 2);
    MarkMirrorWallHalvedZone(attackerZone);
  }

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = MIRROR_WALL;
    gCardEffectTextData.cardId2 = attackerCardId;
    ActivateCardEffectText();
  }
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MirrorWall_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = MIRROR_WALL;
  zone.isFaceUp = TRUE;
  if (!IsActivatedMirrorWallZone(&zone))
    __builtin_trap();
}
#endif
