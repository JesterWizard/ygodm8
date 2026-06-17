#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "graveyard_effects.h"
#include "kaiser_glider.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);


static u8 CanReturnMonsterAtZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 fixedDuelist;
  u8 turnDuelist;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist == 0xFF)
    return FALSE;

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist])
      return FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0;
  }

  return FALSE;
}

static u8 FindFirstKaiserGliderTarget(u8 *outRow, u8 *outCol)
{
  u8 row;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!CanReturnMonsterAtZone(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 FieldHasKaiserGliderTarget(void)
{
  u8 row;
  u8 col;

  return FindFirstKaiserGliderTarget(&row, &col);
}

static u16 GetZoneAttackPoints(struct DuelCard *zone)
{
  ApplyFieldZoneStatsToCardInfo(zone);
  return gCardInfo.atk;
}

static u8 PickAiKaiserGliderTarget(u8 *outRow, u8 *outCol)
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

      if (!CanReturnMonsterAtZone(row, col))
        continue;

      zone = gFixedZones[row][col];
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

  return FindFirstKaiserGliderTarget(outRow, outCol);
}

static u8 KaiserGliderOwnerIsPlayer(void)
{
  u8 turnDuelist = (gActiveEffect.turnRow == 7) ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER];
}

static void ResolveKaiserGliderEffectForAi(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!PickAiKaiserGliderTarget(&targetRow, &targetCol))
    return;

  Duel_ReturnMonsterZoneToOwnerHand(gFixedZones[targetRow][targetCol], TRUE);
}

unsigned char ShouldActivateKaiserGlider(void)
{
  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != KAISER_GLIDER)
    return FALSE;

  if (!FieldHasKaiserGliderTarget())
    return FALSE;

  if (gActiveEffect.turnRow == 7)
    return gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == KAISER_GLIDER;

  return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == KAISER_GLIDER;
}

void BeginKaiserGliderTargeting(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstKaiserGliderTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.state = DUEL_CURSOR_KAISER_GLIDER_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(PLAYER_MONSTER_ROW, targetRow);
}

void TrySelectKaiserGliderTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!CanReturnMonsterAtZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  Duel_ReturnMonsterZoneToOwnerHand(gFixedZones[targetRow][targetCol], TRUE);
  gDuelCursor.state = 0;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  TryActivatingPermanentEffects();
}

void CancelKaiserGliderTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

void ActivateKaiserGlider(void)
{
  u8 turnDuelist = (gActiveEffect.turnRow == 7) ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  if (!FieldHasKaiserGliderTarget())
    return;

  Duel_ShowEffectText(KAISER_GLIDER);
  GetGraveCardAndClearGrave(turnDuelist);

  if (KaiserGliderOwnerIsPlayer())
    BeginKaiserGliderTargeting();
  else
    ResolveKaiserGliderEffectForAi();
}
