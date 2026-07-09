#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/card_effect_texts.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "mini_card.h"
#include "raviel_lord_of_phantasms.h"

void UpdateDuelGfxExceptField(void);

static u8 IsOnActiveDuelistMonsterRow(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gMonEffect.row == PLAYER_MONSTER_ROW;
  return gMonEffect.row == OPPONENT_MONSTER_ROW;
}

static u8 IsValidTribute(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ACTIVE_DUELIST_MONSTER_ROW && fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (zone->isLocked)
    return FALSE;
  if (zone->id == RAVIEL_LORD_OF_PHANTASMS)
    return FALSE;

  return TRUE;
}

static u8 FieldHasTributeTarget(void)
{
  u8 row;
  u8 col;

  for (row = 0; row <= 1; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTribute(row, col))
        return TRUE;
    }
  }
  return FALSE;
}

static u8 ScoreTribute(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u8 fixedDuelist = (fixedRow == ACTIVE_DUELIST_MONSTER_ROW)
      ? (WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT)
      : (WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER);

  if (zone->id == CARD_NONE)
    return 0;

  SetCardInfo(zone->id);
  /* Prefer own monsters over opponent's */
  if (fixedDuelist == (WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER))
    return 100 + gCardInfo.atk;

  return gCardInfo.atk;
}

static u8 AiPickTribute(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;
  u8 bestScore = 0;

  for (row = 0; row <= 1; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      u8 score;

      if (!IsValidTribute(row, col))
        continue;

      score = ScoreTribute(row, col);
      if (score > bestScore) {
        bestScore = score;
        bestRow = row;
        bestCol = col;
      }
    }
  }

  if (bestRow == 0xFF)
    return FALSE;

  *outRow = bestRow;
  *outCol = bestCol;
  return TRUE;
}

u8 CanActivateRAVIEL_LORD_OF_PHANTASMS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != RAVIEL_LORD_OF_PHANTASMS)
    return FALSE;

  if (!IsOnActiveDuelistMonsterRow())
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTributeTarget();
}

void ActivateRAVIEL_LORD_OF_PHANTASMSEffect(void)
{
  u8 bestRow;
  u8 bestCol;
  struct DuelCard *selfZone;
  struct DuelCard *tributeZone;
  u16 originalAtk;
  u8 graveyardDuelist;

  Duel_ShowCardEffectText(RAVIEL_LORD_OF_PHANTASMS,
                          CARD_EFFECT_TEXT_RAVIEL_LORD_OF_PHANTASMS_POPUP_1);

  if (IsDuelOver() == TRUE)
    return;

  selfZone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  MarkMonsterEffectUsed(selfZone);

  if (!AiPickTribute(&bestRow, &bestCol))
    return;

  tributeZone = gFixedZones[bestRow][bestCol];

  SetCardInfo(tributeZone->id);
  originalAtk = gCardInfo.atk;

  graveyardDuelist = (bestRow == ACTIVE_DUELIST_MONSTER_ROW)
      ? (WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT)
      : (WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER);

  if (Duel_DestroyZone(tributeZone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (originalAtk > 0)
    selfZone->permStage += (s8)((u32)originalAtk / (u32)100);
  else
    selfZone->permStage += (s8)1;

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
