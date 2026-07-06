#include "global.h"
#include "common-chax.h"
#include "ai_sim.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "permanent_effect.h"
#include "yubel.h"

extern u8 gIsPlayerTurnOver;

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);

void Yubel_ClearTurnState(void)
{
  gYubelEndPhaseResolvedThisTurn = FALSE;
}

static u8 ActiveDuelistMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 GraveyardDuelistForMonsterFixedRow(u8 fixedRow)
{
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 IsValidYubelTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  if (fixedRow == gYubelTributeOriginRow && fixedCol == gYubelTributeOriginCol)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return GetDuelistForZone(zone) == gYubelTributeOwner;
}

static u8 FindFirstYubelTributeTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidYubelTributeTarget(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 HasYubelTributeTarget(void)
{
  u8 row;
  u8 col;

  return FindFirstYubelTributeTarget(&row, &col);
}

static void ResolveYubelTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!IsValidYubelTributeTarget(fixedRow, fixedCol))
    return;

  zone = gFixedZones[fixedRow][fixedCol];
  PlayMusic(SFX_TRIBUTE);
  Duel_DestroyZone(zone, GraveyardDuelistForMonsterFixedRow(fixedRow), TRUE);
  gYubelEndPhaseResolvedThisTurn = TRUE;
}

static u8 AiPickYubelTributeTarget(u8 *outRow, u8 *outCol)
{
  return FindFirstYubelTributeTarget(outRow, outCol);
}

static u8 GraveyardDuelistForMonsterTurnRow(u8 turnRow)
{
  return turnRow == ACTIVE_DUELIST_MONSTER_ROW ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 IsYubelEligibleForEndPhase(const struct DuelCard *zone)
{
  if (zone->id != YUBEL)
    return FALSE;

  /* ponytail: hand normal/tribute summon copies isFaceUp=0; attack-position still counts */
  return zone->isFaceUp || !zone->isDefending;
}

static u8 IsYubelTerrorEligibleForEndPhase(const struct DuelCard *zone)
{
  if (zone->id != YUBEL_TERROR_INCARNATE)
    return FALSE;

  return zone->isFaceUp || !zone->isDefending;
}

static struct DuelCard *FindYubelForActiveDuelistEndPhase(u8 *outFixedCol)
{
  u8 col;
  u8 row = ActiveDuelistMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (IsYubelEligibleForEndPhase(zone)) {
      *outFixedCol = col;
      return zone;
    }
  }

  return NULL;
}

static void BeginYubelTributeTargeting(u8 originRow, u8 originCol)
{
  u8 row;
  u8 col;

  if (!FindFirstYubelTributeTarget(&row, &col))
    return;

  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;
  PlayMusic(SFX_SELECT);
  gDuelCursor.state = DUEL_CURSOR_YUBEL_TRIBUTE_TARGET;
  gDuelCursor.currentY = row;
  gDuelCursor.currentX = col;
  DisplayCardInfoBar();
  sub_8041E70(originRow, row);
}

static void BeginYubelEndPhase(struct DuelCard *zone, u8 fixedRow, u8 fixedCol)
{
  u8 owner;

  owner = GetDuelistForZone(zone);
  if (owner == 0xFF)
    return;

  gYubelTributeOwner = owner;
  gYubelTributeOriginRow = fixedRow;
  gYubelTributeOriginCol = fixedCol;
  gActiveEffect.turnRow = ACTIVE_DUELIST_MONSTER_ROW;
  gActiveEffect.col = fixedCol;
  gActiveEffect.cardId = YUBEL;

  ResetCardEffectTextData();
  Duel_ShowEffectText(YUBEL);

  if (IsDuelOver() == TRUE)
    return;

  if (!HasYubelTributeTarget()) {
    gYubelSelfDestructActive = TRUE;
    Duel_DestroyZone(zone, GraveyardDuelistForMonsterFixedRow(fixedRow), TRUE);
    gYubelEndPhaseResolvedThisTurn = TRUE;
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER) {
    BeginYubelTributeTargeting(fixedRow, fixedCol);
  } else {
    u8 row;
    u8 col;

    if (AiPickYubelTributeTarget(&row, &col))
      ResolveYubelTributeTarget(row, col);
  }
}

void TrySelectYubelTributeTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsValidYubelTributeTarget(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  ResolveYubelTributeTarget(targetRow, targetCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();

  gIsPlayerTurnOver = 1;
}

unsigned char ShouldActivateYubelEndPhase(void)
{
  u8 col;

  return FindYubelForActiveDuelistEndPhase(&col) != NULL;
}

void ActivateYubelEndPhase(void)
{
  u8 col;
  struct DuelCard *zone = FindYubelForActiveDuelistEndPhase(&col);

  if (zone == NULL)
    return;

  BeginYubelEndPhase(zone, ActiveDuelistMonsterFixedRow(), col);
}

unsigned char ShouldActivateYubelTerrorEndPhase(void)
{
  u8 col;
  u8 row = ActiveDuelistMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (IsYubelTerrorEligibleForEndPhase(zone))
      return TRUE;
  }

  return FALSE;
}

void ActivateYubelTerrorEndPhase(void)
{
  u8 col;
  u8 selfRow = ActiveDuelistMonsterFixedRow();
  u8 row;
  struct DuelCard *selfZone = NULL;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsYubelTerrorEligibleForEndPhase(gFixedZones[selfRow][col])) {
      selfZone = gFixedZones[selfRow][col];
      break;
    }
  }

  if (selfZone == NULL)
    return;

  gActiveEffect.turnRow = ACTIVE_DUELIST_MONSTER_ROW;
  gActiveEffect.col = col;
  gActiveEffect.cardId = YUBEL_TERROR_INCARNATE;

  Duel_ShowCardEffectText(YUBEL_TERROR_INCARNATE,
                          CARD_EFFECT_TEXT_YUBEL_TERROR_INCARNATE_POPUP_2);

  if (IsDuelOver() == TRUE)
    return;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone == selfZone || zone->id == CARD_NONE)
        continue;

      if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
        continue;

      if (IsGodCard(zone->id))
        continue;

      if (Duel_DestroyZone(zone, GraveyardDuelistForMonsterTurnRow(row), TRUE)
          == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }
}

void TryApplyYubelEndPhaseEffect(void)
{
  u8 col;
  struct DuelCard *zone;

  if (IsDuelOver() == TRUE || gAiSimInBatch)
    return;

  zone = FindYubelForActiveDuelistEndPhase(&col);
  if (zone == NULL)
    return;

  BeginYubelEndPhase(zone, ActiveDuelistMonsterFixedRow(), col);
}

static u8 TryApplyYubelTerrorEndPhaseEffectInternal(void)
{
  u8 col;
  u8 row = ActiveDuelistMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsYubelTerrorEligibleForEndPhase(gFixedZones[row][col]))
      continue;

    ActivateYubelTerrorEndPhase();
    return TRUE;
  }

  return FALSE;
}

void TryApplyYubelTerrorEndPhaseEffect(void)
{
  if (IsDuelOver() == TRUE || gAiSimInBatch)
    return;

  TryApplyYubelTerrorEndPhaseEffectInternal();
}

void ResolveYubelEndPhaseEffectsAtTurnEnd(void)
{
  u8 col;

  if (gYubelEndPhaseResolvedThisTurn || IsDuelOver() == TRUE || gAiSimInBatch)
    return;

  if (FindYubelForActiveDuelistEndPhase(&col) != NULL) {
    TryApplyYubelEndPhaseEffect();
    if (IsDuelOver() == TRUE)
      return;
    if (gDuelCursor.state == DUEL_CURSOR_YUBEL_TRIBUTE_TARGET)
      return;
  }

  if (TryApplyYubelTerrorEndPhaseEffectInternal())
    gYubelEndPhaseResolvedThisTurn = TRUE;
}

u8 Yubel_ConfirmTurnEndFromMenu(void)
{
  ResolveYubelEndPhaseEffectsAtTurnEnd();
  if (IsDuelOver() == TRUE)
    return TRUE;

  return gDuelCursor.state != DUEL_CURSOR_YUBEL_TRIBUTE_TARGET;
}
