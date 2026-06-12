#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "graveyard_effects.h"
#include "kaiser_glider.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);

static u8 TurnDuelistToFixed(u8 duelist)
{
  if (gTurnDuelistBattleState[duelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 FixedDuelistToTurnDuelist(u8 fixedDuelist)
{
  u8 duelist;

  for (duelist = 0; duelist < 2; duelist++) {
    if (gTurnDuelistBattleState[duelist] == &gDuel.duelistbattleState[fixedDuelist])
      return duelist;
  }

  return ACTIVE_DUELIST;
}

static u8 IsMonsterFieldRow(u8 fixedRow)
{
  return fixedRow == PLAYER_MONSTER_ROW || fixedRow == OPPONENT_MONSTER_ROW;
}

static u8 CanReturnMonsterAtZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 fixedDuelist;
  u8 turnDuelist;

  if (!IsMonsterFieldRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist == 0xFF)
    return FALSE;

  turnDuelist = FixedDuelistToTurnDuelist(fixedDuelist);
  return FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0;
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

static u8 ReturnMonsterAtZoneToOwnerHand(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u8 fixedDuelist = GetDuelistForZone(zone);
  u8 turnDuelist;
  s8 handZone;

  if (fixedDuelist == 0xFF)
    return FALSE;

  turnDuelist = FixedDuelistToTurnDuelist(fixedDuelist);
  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  CopyCard(gTurnHands[turnDuelist][handZone], zone);
  gTurnHands[turnDuelist][handZone]->isFaceUp = FALSE;
  gTurnHands[turnDuelist][handZone]->isLocked = FALSE;
  gTurnHands[turnDuelist][handZone]->isDefending = FALSE;
  gTurnHands[turnDuelist][handZone]->unkTwo = 0;
  gTurnHands[turnDuelist][handZone]->unkThree = 0;
  gTurnHands[turnDuelist][handZone]->unk4 = 0;
  gTurnHands[turnDuelist][handZone]->willChangeSides = FALSE;
  ResetPermStage(gTurnHands[turnDuelist][handZone]);
  ResetTempStage(gTurnHands[turnDuelist][handZone]);
  ClearZone(zone);
  return TRUE;
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

static u8 KaiserGliderGraveyardFixedDuelist(void)
{
  if (gActiveEffect.turnRow == 7)
    return TurnDuelistToFixed(INACTIVE_DUELIST);

  return TurnDuelistToFixed(ACTIVE_DUELIST);
}

static void ShowKaiserGliderActivationText(void)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  gCardEffectTextData.cardId = KAISER_GLIDER;
  ActivateCardEffectText();
  gHideEffectText = hideEffectText;
}

static void ResolveKaiserGliderEffectForAi(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!PickAiKaiserGliderTarget(&targetRow, &targetCol))
    return;

  ReturnMonsterAtZoneToOwnerHand(targetRow, targetCol);
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

  ReturnMonsterAtZoneToOwnerHand(targetRow, targetCol);
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
  u8 fixedOwner = KaiserGliderGraveyardFixedDuelist();

  if (!FieldHasKaiserGliderTarget())
    return;

  ShowKaiserGliderActivationText();
  GetGraveCardAndClearGrave2(gActiveEffect.turnRow == 6
      ? TurnDuelistToFixed(ACTIVE_DUELIST)
      : TurnDuelistToFixed(INACTIVE_DUELIST));

  if (fixedOwner == DUEL_PLAYER)
    BeginKaiserGliderTargeting();
  else
    ResolveKaiserGliderEffectForAi();
}
