#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "ryu_kishin_clown.h"

extern unsigned char IsSkillDrainActiveOnField(void);
extern unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId);

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 IsFaceUpMonsterTarget(struct DuelCard *zone)
{
  if (zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  /* Attack-position monsters stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 IsValidRyuKishinClownTargetZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return IsFaceUpMonsterTarget(zone);
}

static u8 FindFirstRyuKishinClownTarget(u8 *outRow, u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidRyuKishinClownTargetZone(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u16 GetZoneAttackPoints(struct DuelCard *zone)
{
  ApplyFieldZoneStatsToCardInfo(zone);
  return gCardInfo.atk;
}

static void ToggleMonsterBattlePosition(u8 targetRow, u8 targetCol)
{
  struct DuelCard *zone = gFixedZones[targetRow][targetCol];

  zone->isDefending = !zone->isDefending;
  zone->isFaceUp = TRUE;
  Duel_NotifyFixedMonsterRowChanged(targetRow);
  Duel_NotifyMonsterZoneChanged(zone);
}

static void MarkRyuKishinClownEffectUsed(struct DuelCard *zone)
{
  zone->unk4 = 1;
}

static u8 PickAiRyuKishinClownTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!IsValidRyuKishinClownTargetZone(row, col))
        continue;

      zone = gFixedZones[row][col];
      if (zone->isDefending)
        continue;

      atk = GetZoneAttackPoints(zone);
      if (bestRow == 0xFF || atk > bestAtk) {
        bestRow = row;
        bestCol = col;
        bestAtk = atk;
      }
    }
  }

  if (bestRow != 0xFF) {
    *outRow = bestRow;
    *outCol = bestCol;
    return TRUE;
  }

  return FindFirstRyuKishinClownTarget(outRow, outCol);
}

static void ResolveRyuKishinClownTarget(u8 targetRow, u8 targetCol, struct DuelCard *sourceZone)
{
  if (!IsValidRyuKishinClownTargetZone(targetRow, targetCol))
    return;

  ToggleMonsterBattlePosition(targetRow, targetCol);
  MarkRyuKishinClownEffectUsed(sourceZone);
  Duel_RefreshMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void BeginRyuKishinClownTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstRyuKishinClownTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_RYU_KISHIN_CLOWN_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originFixedRow, targetRow);
}

static void ResolveRyuKishinClownEffectForAi(struct DuelCard *sourceZone, u8 originFixedRow,
                                             u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  (void)originFixedRow;
  (void)originFixedCol;

  if (!PickAiRyuKishinClownTarget(&targetRow, &targetCol))
    return;

  ResolveRyuKishinClownTarget(targetRow, targetCol, sourceZone);
}

static u8 RyuKishinClownMayActivateFromZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != RYU_KISHIN_CLOWN || zone->unk4 == 1)
    return FALSE;

  if (!IsFaceUpMonsterTarget(zone))
    return FALSE;

  {
    u8 row;
    u8 col;

    return FindFirstRyuKishinClownTarget(&row, &col);
  }
}

static void ActivateRyuKishinClownFromZone(struct DuelCard *zone, u8 fixedRow, u8 fixedCol)
{
  Duel_ShowEffectTextTyped(RYU_KISHIN_CLOWN, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER && fixedRow == PLAYER_MONSTER_ROW) {
    BeginRyuKishinClownTargeting(fixedRow, fixedCol);
    return;
  }

  ResolveRyuKishinClownEffectForAi(zone, fixedRow, fixedCol);
}

void TryActivateRyuKishinClownOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (!RyuKishinClownMayActivateFromZone(zone))
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  if (IsSkillDrainActiveOnField()
      && TryActivateSkillDrainAndNegateCardId(RYU_KISHIN_CLOWN))
    return;

  ActivateRyuKishinClownFromZone(zone, fixedRow, fixedCol);
}

unsigned char CanActivateRyuKishinClown(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != RYU_KISHIN_CLOWN)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  return RyuKishinClownMayActivateFromZone(zone);
}

void ActivateRyuKishinClownEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  ActivateRyuKishinClownFromZone(zone, gMonEffect.row, gMonEffect.zone);
}

void TrySelectRyuKishinClownTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;
  struct DuelCard *sourceZone = gFixedZones[originRow][originCol];

  if (!IsValidRyuKishinClownTargetZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  ResolveRyuKishinClownTarget(targetRow, targetCol, sourceZone);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
}

void CancelRyuKishinClownTargeting(void)
{
  PlayMusic(SFX_FORBIDDEN);
  WaitForVBlank();
}
