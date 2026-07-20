#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "elemental_hero_tempest.h"
#include "monster_effect_usage.h"

extern void UpdateDuelGfxExceptField(void);

extern u8 gElementalHeroTempestPickPhase;
extern u8 gElementalHeroTempestOriginRow;
extern u8 gElementalHeroTempestOriginCol;

#define TEMPEST_PICK_COST 1
#define TEMPEST_PICK_PROTECT 2

static u8 ActiveMonsterRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 ActiveBackrow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

static u8 IsTempestOriginZone(u8 fixedRow, u8 fixedCol)
{
  return fixedRow == gElementalHeroTempestOriginRow && fixedCol == gElementalHeroTempestOriginCol;
}

static u8 ZoneOnActiveSide(u8 fixedRow)
{
  return fixedRow == ActiveMonsterRow() || fixedRow == ActiveBackrow();
}

static u8 IsValidCostZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!ZoneOnActiveSide(fixedRow) || IsTempestOriginZone(fixedRow, fixedCol))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone->id != CARD_NONE;
}

static u8 IsValidProtectZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 FieldHasTempestCost(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidCostZone(ActiveMonsterRow(), col))
      return TRUE;
    if (IsValidCostZone(ActiveBackrow(), col))
      return TRUE;
  }

  return FALSE;
}

void ClearElementalHeroTempestProtection(void)
{
  gElementalHeroTempestAnchorRow = ELEMENTAL_HERO_TEMPEST_ZONE_NONE;
  gElementalHeroTempestAnchorCol = ELEMENTAL_HERO_TEMPEST_ZONE_NONE;
  gElementalHeroTempestProtectedRow = ELEMENTAL_HERO_TEMPEST_ZONE_NONE;
  gElementalHeroTempestProtectedCol = ELEMENTAL_HERO_TEMPEST_ZONE_NONE;
  gElementalHeroTempestPickPhase = 0;
}

void ElementalHeroTempestSetProtection(u8 anchorRow, u8 anchorCol, u8 protectedRow,
                                       u8 protectedCol)
{
  gElementalHeroTempestAnchorRow = anchorRow;
  gElementalHeroTempestAnchorCol = anchorCol;
  gElementalHeroTempestProtectedRow = protectedRow;
  gElementalHeroTempestProtectedCol = protectedCol;
}

u8 ElementalHeroTempestProtectsBattleZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *tempestZone;
  struct DuelCard *protectedZone;

  if (gElementalHeroTempestProtectedRow == ELEMENTAL_HERO_TEMPEST_ZONE_NONE)
    return FALSE;

  if (fixedRow != gElementalHeroTempestProtectedRow
      || fixedCol != gElementalHeroTempestProtectedCol)
    return FALSE;

  if (gElementalHeroTempestAnchorRow == ELEMENTAL_HERO_TEMPEST_ZONE_NONE)
    return FALSE;

  tempestZone = gFixedZones[gElementalHeroTempestAnchorRow][gElementalHeroTempestAnchorCol];
  if (tempestZone->id != ELEMENTAL_HERO_TEMPEST || !tempestZone->isFaceUp)
    return FALSE;

  protectedZone = gFixedZones[fixedRow][fixedCol];
  return protectedZone->id != CARD_NONE
      && GetTypeGroup(protectedZone->id) == TYPE_GROUP_MONSTER;
}

static void SendCostToGraveyard(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  PlayMusic(SFX_TRIBUTE);
  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  if (gElementalHeroTempestPickPhase == TEMPEST_PICK_COST)
    return IsValidCostZone(fixedRow, fixedCol);

  return IsValidProtectZone(fixedRow, fixedCol);
}

static void BeginProtectTargeting(void)
{
  gElementalHeroTempestPickPhase = TEMPEST_PICK_PROTECT;

  if (WhoseTurn() != DUEL_PLAYER)
    return;

  Duel_EnterPickZoneTargeting();
}

static void ResolveProtectTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidProtectZone(fixedRow, fixedCol))
    return;

  ElementalHeroTempestSetProtection(gElementalHeroTempestOriginRow, gElementalHeroTempestOriginCol, fixedRow,
                                    fixedCol);
  UpdateDuelGfxExceptField();
}

static void ResolveCostTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidCostZone(fixedRow, fixedCol))
    return;

  SendCostToGraveyard(fixedRow, fixedCol);

  if (IsDuelOver() == TRUE)
    return;

  BeginProtectTargeting();
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  if (gElementalHeroTempestPickPhase == TEMPEST_PICK_COST)
    ResolveCostTarget(fixedRow, fixedCol);
  else
    ResolveProtectTarget(fixedRow, fixedCol);
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickCost(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidCostZone(ActiveBackrow(), col)) {
      *outRow = ActiveBackrow();
      *outCol = col;
      return TRUE;
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidCostZone(ActiveMonsterRow(), col)) {
      *outRow = ActiveMonsterRow();
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 AiPickProtect(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidProtectZone(ActiveMonsterRow(), col))
      continue;

    zone = gFixedZones[ActiveMonsterRow()][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outRow = ActiveMonsterRow();
  *outCol = bestCol;
  return TRUE;
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  if (gElementalHeroTempestPickPhase == TEMPEST_PICK_COST)
    return AiPickCost(outRow, outCol);

  return AiPickProtect(outRow, outCol);
}

static void ResolveTempestEffectForAi(void)
{
  u8 row;
  u8 col;

  if (!AiPickCost(&row, &col))
    return;

  if (Duel_MonsterEffectConfirmTargetForAi(ELEMENTAL_HERO_TEMPEST, row, col))
    return;

  ResolveCostTarget(row, col);

  if (IsDuelOver() == TRUE || gElementalHeroTempestPickPhase != TEMPEST_PICK_PROTECT)
    return;

  if (!AiPickProtect(&row, &col))
    return;

  if (Duel_MonsterEffectConfirmTargetForAi(ELEMENTAL_HERO_TEMPEST, row, col))
    return;

  ResolveProtectTarget(row, col);
}

unsigned char CanActivateElementalHeroTempest(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_TEMPEST)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTempestCost();
}

void ActivateElementalHeroTempestEffect(void)
{
  gElementalHeroTempestOriginRow = gMonEffect.row;
  gElementalHeroTempestOriginCol = gMonEffect.zone;
  gElementalHeroTempestPickPhase = TEMPEST_PICK_COST;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_TEMPEST, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gElementalHeroTempestOriginRow;
  gDuelCursor.destX = gElementalHeroTempestOriginCol;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    ResolveTempestEffectForAi();
}
