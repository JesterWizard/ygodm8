#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "man_thro_tro.h"
#include "monster_effect_usage.h"
#include "ojama_trio.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(void);

static u8 IsManThroTroTributeMonster(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  /* Ojama Trio monster form is the only token-like field unit today */
  if (OjamaTrioZoneIsMonsterForm(zone))
    return FALSE;

  SetCardInfo(zone->id);

  if (gCardInfo.color != COLOR_NORMAL)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 IsValidManThroTroTributeZone(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  return IsManThroTroTributeMonster(gFixedZones[fixedRow][fixedCol]);
}

static u8 FindFirstManThroTroTributeTarget(u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidManThroTroTributeZone(PLAYER_MONSTER_ROW, col))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ApplyManThroTroDamage(void)
{
  u8 target = (WhoseTurn() == DUEL_PLAYER) ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  Duel_ChangeLp(target, -(s32)MAN_THRO_TRO_DAMAGE, TRUE);
}

static void SacrificeFixedMonster(u8 fixedRow, u8 fixedCol)
{
  PlayMusic(SFX_TRIBUTE);
  ClearZoneAndSendMonToGraveyard2(gFixedZones[fixedRow][fixedCol], DUEL_PLAYER);
}

static u8 FindAiManThroTroTributeCol(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (IsManThroTroTributeMonster(zone))
      return col;
  }

  return MAX_ZONES_IN_ROW;
}

static void ResolveManThroTroEffectForAi(void)
{
  u8 tributeCol = FindAiManThroTroTributeCol();
  struct DuelCard *zone;

  if (tributeCol >= MAX_ZONES_IN_ROW)
    return;

  zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][tributeCol];
  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  ApplyManThroTroDamage();
}

unsigned char CanActivateManThroTro(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MAN_THRO_TRO)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER) {
    u8 col;

    return FindFirstManThroTroTributeTarget(&col);
  }

  return FindAiManThroTroTributeCol() < MAX_ZONES_IN_ROW;
}

void BeginManThroTroTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetCol;

  if (!FindFirstManThroTroTributeTarget(&targetCol))
    return;

  Duel_ShowEffectTextTyped(MAN_THRO_TRO, 2);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_MAN_THRO_TRO_TARGET;
  gDuelCursor.currentY = PLAYER_MONSTER_ROW;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(originFixedRow, PLAYER_MONSTER_ROW);
}

void TrySelectManThroTroTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsValidManThroTroTributeZone(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  SacrificeFixedMonster(targetRow, targetCol);
  ApplyManThroTroDamage();

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != 1)
    TryActivatingPermanentEffects();
}

void ActivateManThroTroEffect(void)
{
  if (WhoseTurn() == DUEL_PLAYER) {
    BeginManThroTroTargeting(gMonEffect.row, gMonEffect.zone);
    return;
  }

  Duel_ShowEffectTextTyped(MAN_THRO_TRO, 2);

  if (IsDuelOver() == TRUE)
    return;

  ResolveManThroTroEffectForAi();
}
