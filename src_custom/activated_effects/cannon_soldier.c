#include "global.h"
#include "common-chax.h"
#include "cannon_soldier.h"
#include "monster_effect_usage.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(void);

static u8 IsValidCannonSoldierTributeZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone->id != CARD_NONE;
}

static u8 FindFirstCannonSoldierTributeTarget(u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidCannonSoldierTributeZone(PLAYER_MONSTER_ROW, col))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u16 GetZoneAttackPoints(struct DuelCard *zone)
{
  ApplyFieldZoneStatsToCardInfo(zone);
  return gCardInfo.atk;
}

static void ApplyCannonSoldierDamage(u16 damage)
{
  if (damage == 0)
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    SetOpponentLifePointsToSubtract(damage);
  else
    SetPlayerLifePointsToSubtract(damage);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
}

static void SacrificeFixedMonster(u8 fixedRow, u8 fixedCol)
{
  PlayMusic(SFX_TRIBUTE);
  ClearZoneAndSendMonToGraveyard2(gFixedZones[fixedRow][fixedCol], DUEL_PLAYER);
}

static u8 SacrificeTurnMonsterForAi(u8 avoidCol)
{
  u8 col;
  u8 fallbackCol = MAX_ZONES_IN_ROW;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id == CARD_NONE)
      continue;

    if (col != avoidCol)
      return col;

    fallbackCol = col;
  }

  return fallbackCol;
}

static void ResolveCannonSoldierEffectForAi(void)
{
  u8 tributeCol = SacrificeTurnMonsterForAi(gMonEffect.zone);
  struct DuelCard *zone;
  u16 damage;

  if (tributeCol >= MAX_ZONES_IN_ROW)
    return;

  zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][tributeCol];
  damage = GetZoneAttackPoints(zone);
  ClearZoneAndSendMonToGraveyard(zone, ACTIVE_DUELIST);
  ApplyCannonSoldierDamage(damage);
}

u8 IsCannonSoldierCard(u16 cardId)
{
  return cardId == CANNON_SOLDIER;
}

u8 FieldHasCannonSoldierTributeTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 col;

  (void)originFixedRow;
  (void)originFixedCol;
  return FindFirstCannonSoldierTributeTarget(&col);
}

unsigned char CanActivateCannonSoldier(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CANNON_SOLDIER)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return FieldHasCannonSoldierTributeTarget(gMonEffect.row, gMonEffect.zone);

  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < MAX_ZONES_IN_ROW;
}

void BeginCannonSoldierTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;

  if (!FindFirstCannonSoldierTributeTarget(&targetCol))
    return;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = CANNON_SOLDIER;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_CANNON_SOLDIER_TARGET;
  gDuelCursor.currentY = PLAYER_MONSTER_ROW;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originFixedRow, PLAYER_MONSTER_ROW);
}

void TrySelectCannonSoldierTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsValidCannonSoldierTributeZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  {
    struct DuelCard *zone = gFixedZones[targetRow][targetCol];
    u16 damage = GetZoneAttackPoints(zone);

    SacrificeFixedMonster(targetRow, targetCol);
    ApplyCannonSoldierDamage(damage);
  }

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != 1)
    TryActivatingPermanentEffects();
}

void ActivateCannonSoldierEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER) {
    BeginCannonSoldierTargeting(gMonEffect.row, gMonEffect.zone);
    return;
  }

  ResolveCannonSoldierEffectForAi();
  if (!gHideEffectText) {
    gCardEffectTextData.cardId = CANNON_SOLDIER;
    ActivateCardEffectText();
  }
}
