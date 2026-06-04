#include "global.h"
#include "common-chax.h"
#include "dynamic_equip.h"

extern const u8 gActivationDescription_SliferTheSkyDragon[];

void UpdateDuelGfxExceptField(void);

extern u8 gSliferPendingPenaltyActive;
extern u8 gSliferPendingPenaltyBoardRow;
extern u8 gSliferPendingPenaltyCol;

#define SLIFER_SUMMON_PENALTY_STAGES 4

// board[1] = opponent monster row, board[2] = player monster row (fixed POV)
#define OPPONENT_MONSTER_BOARD_ROW 1
#define PLAYER_MONSTER_BOARD_ROW     2

static u8 GetSliferControllerDuelist(void) {
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[PLAYER_MONSTER_ROW][col]->id == SLIFER_THE_SKY_DRAGON)
      return DUEL_PLAYER;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[OPPONENT_MONSTER_ROW][col]->id == SLIFER_THE_SKY_DRAGON)
      return DUEL_OPPONENT;
  }

  return 0xFF;
}

static u8 ZoneIsOnBoardRow(const struct DuelCard *zone, u8 boardRow) {
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (&gDuel.board[boardRow][col] == zone)
      return TRUE;
  }

  return FALSE;
}

static u8 ZoneIsInAnyHand(const struct DuelCard *zone) {
  u8 duelist;
  u8 col;

  for (duelist = 0; duelist < 2; duelist++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (zone == &gDuel.hands[duelist][col])
        return TRUE;
    }
  }

  return FALSE;
}

static u8 GetOpponentMonsterBoardRow(u8 sliferDuelist) {
  return sliferDuelist == DUEL_PLAYER
      ? OPPONENT_MONSTER_BOARD_ROW
      : PLAYER_MONSTER_BOARD_ROW;
}

static u8 ZoneIsOpponentMonsterRowForSlifer(const struct DuelCard *zone, u8 sliferDuelist) {
  return ZoneIsOnBoardRow(zone, GetOpponentMonsterBoardRow(sliferDuelist));
}

static u8 ZoneAtkIsZero(struct DuelCard *zone) {
  struct StatMod statMod;

  if (zone->id == CARD_NONE)
    return FALSE;

  statMod.card = zone->id;
  statMod.field = gDuel.field;
  statMod.stage = GetFinalStage(zone);
  SetFinalStat(&statMod);
  return gCardInfo.atk == 0;
}

static void ShowSliferSummonPenaltyText(void) {
  if (gHideEffectText)
    return;

  ResetCardEffectTextData();
  gCardEffectTextData.cardId = SLIFER_THE_SKY_DRAGON;
  ActivateCardEffectText();
}

static void ApplySummonPenaltyStages(struct DuelCard *summonedZone) {
  u8 i;

  for (i = 0; i < SLIFER_SUMMON_PENALTY_STAGES; i++)
    DecrementTempStage(summonedZone);
}

static u8 IsHandMonsterSummonToField(struct DuelCard *dst, struct DuelCard *src) {
  if (!ZoneIsInAnyHand(src))
    return FALSE;

  if (src->id == CARD_NONE || GetTypeGroup(src->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (src->id == SLIFER_THE_SKY_DRAGON)
    return FALSE;

  return ZoneIsOnBoardRow(dst, OPPONENT_MONSTER_BOARD_ROW)
      || ZoneIsOnBoardRow(dst, PLAYER_MONSTER_BOARD_ROW);
}

u8 ShouldApplySliferSummonPenalty(struct DuelCard *dst, struct DuelCard *src) {
  return IsHandMonsterSummonToField(dst, src);
}

static struct DuelCard *ZoneFromBoardCoords(u8 boardRow, u8 col) {
  if (boardRow >= 4 || col >= MAX_ZONES_IN_ROW)
    return NULL;

  return &gDuel.board[boardRow][col];
}

static void QueuePenaltyZone(struct DuelCard *zone) {
  u8 boardRow;
  u8 col;

  for (boardRow = 0; boardRow < 4; boardRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (&gDuel.board[boardRow][col] == zone) {
        gSliferPendingPenaltyBoardRow = boardRow;
        gSliferPendingPenaltyCol = col;
        gSliferPendingPenaltyActive = TRUE;
        return;
      }
    }
  }
}

void ClearPendingSliferSummonPenalty(void) {
  gSliferPendingPenaltyActive = FALSE;
}

static void ApplySliferSummonPenaltyToZone(struct DuelCard *summonedZone) {
  u8 graveyardDuelist;

  if (summonedZone == NULL || summonedZone->id == CARD_NONE)
    return;

  ShowSliferSummonPenaltyText();
  ApplySummonPenaltyStages(summonedZone);

  if (!ZoneAtkIsZero(summonedZone))
    return;

  graveyardDuelist = GetDuelistForZone(summonedZone);
  if (graveyardDuelist == 0xFF)
    return;

  ClearZoneAndSendMonToGraveyard(summonedZone, graveyardDuelist);
  CheckLoserFlags();
}

void ResolvePendingSliferSummonPenalty(void) {
  struct DuelCard *zone;

  if (gSliferPendingPenaltyActive != TRUE)
    return;

  gSliferPendingPenaltyActive = FALSE;
  zone = ZoneFromBoardCoords(gSliferPendingPenaltyBoardRow, gSliferPendingPenaltyCol);

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  ApplySliferSummonPenaltyToZone(zone);
  UpdateDuelGfxExceptField();
}

void MaybeApplySliferSummonPenaltyAfterCopy(struct DuelCard *dst) {
  u8 sliferDuelist;

  if (gHideEffectText == TRUE)
    return;

  if (dst->id == CARD_NONE || GetTypeGroup(dst->id) != TYPE_GROUP_MONSTER)
    return;
  if (dst->id == SLIFER_THE_SKY_DRAGON)
    return;

  sliferDuelist = GetSliferControllerDuelist();
  if (sliferDuelist == 0xFF)
    return;
  if (!ZoneIsOpponentMonsterRowForSlifer(dst, sliferDuelist))
    return;

  QueuePenaltyZone(dst);
}
