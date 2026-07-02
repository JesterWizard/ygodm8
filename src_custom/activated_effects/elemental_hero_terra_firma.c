#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "elemental_hero_terra_firma.h"
#include "monster_effect_usage.h"
#include "riryoku.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 ActiveMonsterRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 RowHasFaceUpTerraFirma(u8 fixedMonsterRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedMonsterRow][col];

    if (zone->id == ELEMENTAL_HERO_TERRA_FIRMA && zone->isFaceUp)
      return TRUE;
  }

  return FALSE;
}

u8 ElementalHeroTerraFirma_RevealsAllyZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  // ponytail: fixed POV — only reveal the player's own monster row
  if (fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  if (!RowHasFaceUpTerraFirma(PLAYER_MONSTER_ROW))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE || zone->isFaceUp)
    return FALSE;

  return Duel_IsElementalHeroCard(zone->id);
}

static u8 ZoneIsTributeableElementalHero(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (zone->id == ELEMENTAL_HERO_TERRA_FIRMA)
    return FALSE;

  if (!Duel_IsElementalHeroCard(zone->id))
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  // ponytail: attack-position summons stay isFaceUp=0 until end-of-turn flip
  return zone->isDefending == FALSE;
}

static u8 IsValidTributeTargetEx(u8 originRow, u8 originCol, u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != originRow || fixedCol == originCol)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return ZoneIsTributeableElementalHero(zone);
}

static u8 IsValidTributeTarget(u8 fixedRow, u8 fixedCol)
{
  return IsValidTributeTargetEx(gMonEffect.row, gMonEffect.zone, fixedRow, fixedCol);
}

static u8 FieldHasTributeTarget(u8 originRow, u8 originCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (col == originCol)
      continue;

    if (IsValidTributeTargetEx(originRow, originCol, originRow, col))
      return TRUE;
  }

  return FALSE;
}

static u8 FindFirstTributeTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidTributeTarget(gMonEffect.row, col))
      continue;

    *outRow = gMonEffect.row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static struct DuelCard *TerraFirmaSourceZone(void)
{
  return gFixedZones[gMonEffect.row][gMonEffect.zone];
}

static void ApplyTributeAtkBoost(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *tributeZone;
  struct DuelCard *terraFirmaZone;
  u16 gainedAtk;

  if (!IsValidTributeTarget(fixedRow, fixedCol))
    return;

  terraFirmaZone = TerraFirmaSourceZone();
  if (terraFirmaZone->id != ELEMENTAL_HERO_TERRA_FIRMA)
    return;

  tributeZone = gFixedZones[fixedRow][fixedCol];
  gainedAtk = Duel_GetZoneFinalAtk(tributeZone);

  PlayMusic(SFX_TRIBUTE);
  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (terraFirmaZone->id != ELEMENTAL_HERO_TERRA_FIRMA)
    return;

  if (gainedAtk > 0) {
    AddRiryokuAtkDelta(terraFirmaZone, (s16)gainedAtk);
    Duel_RefreshMonsterStatOverlays();
  }

  NotifyDynamicEquipFieldChanged();
  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckLevelLimitAreaAAfterFieldChange();
}

static void BeginTerraFirmaTargeting(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstTributeTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  gDuelCursor.state = DUEL_CURSOR_TERRA_FIRMA_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
}

static void FinishTerraFirmaTargeting(u8 originRow, u8 originCol)
{
  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void ResolveTerraFirmaEffectForAi(void)
{
  u8 col;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidTributeTarget(gMonEffect.row, col))
      continue;

    zone = gFixedZones[gMonEffect.row][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return;

  if (Duel_MonsterEffectConfirmTargetForAi(ELEMENTAL_HERO_TERRA_FIRMA, gMonEffect.row, bestCol))
    return;

  ApplyTributeAtkBoost(gMonEffect.row, bestCol);
  FinishTerraFirmaTargeting(gMonEffect.row, gMonEffect.zone);
}

unsigned char CanActivateElementalHeroTerraFirma(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_TERRA_FIRMA)
    return FALSE;

  if (gMonEffect.row != ActiveMonsterRow())
    return FALSE;

  zone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTributeTarget(gMonEffect.row, gMonEffect.zone);
}

void ActivateElementalHeroTerraFirmaEffect(void)
{
  Duel_BeginMonsterEffectResolve();

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_TERRA_FIRMA, 2);

  if (IsDuelOver() != TRUE) {
    if (WhoseTurn() == DUEL_PLAYER)
      BeginTerraFirmaTargeting();
    else
      ResolveTerraFirmaEffectForAi();
  }

  Duel_EndMonsterEffectResolve();
}

void TrySelectElementalHeroTerraFirmaTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!IsValidTributeTarget(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  ApplyTributeAtkBoost(targetRow, targetCol);

  if (IsDuelOver() == TRUE)
    return;

  FinishTerraFirmaTargeting(originRow, originCol);
}

void CancelElementalHeroTerraFirmaTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

#if !defined(__GNUC__)
unsigned char CanActivateElementalHeroTerraFirma(void);
void ActivateElementalHeroTerraFirmaEffect(void);
void TrySelectElementalHeroTerraFirmaTarget(void);
void CancelElementalHeroTerraFirmaTargeting(void);
u8 ElementalHeroTerraFirma_RevealsAllyZone(u8 fixedRow, u8 fixedCol);
#endif
