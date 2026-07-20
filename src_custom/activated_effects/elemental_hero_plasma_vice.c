#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "elemental_hero_plasma_vice.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 IsAttackPositionMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  return zone->isDefending == FALSE;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  return IsAttackPositionMonster(gFixedZones[fixedRow][fixedCol]);
}

static u8 FindFirstTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidTarget(OPPONENT_MONSTER_ROW, col))
      continue;

    *outRow = OPPONENT_MONSTER_ROW;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 GraveyardDuelistForMonsterFixedRow(u8 fixedRow)
{
  if (fixedRow == OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void DestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (Duel_DestroyZone(zone, GraveyardDuelistForMonsterFixedRow(fixedRow), FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);
}

static void ResolveEffectForAi(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  (void)originFixedCol;

  if (!FindFirstTarget(&targetRow, &targetCol))
    return;

  if (Duel_MonsterEffectConfirmTargetForAi(ELEMENTAL_HERO_PLASMA_VICE, targetRow, targetCol))
    return;

  DestroyTarget(targetRow, targetCol);
}

static void BeginDestroyTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_ELEMENTAL_HERO_PLASMA_VICE_TARGET;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(PLAYER_HAND, targetRow);
}

static u8 DiscardCostCard(void)
{
  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return FALSE;

  return IsDuelOver() != TRUE;
}

unsigned char CanActivateElementalHeroPlasmaVice(void)
{
  struct DuelCard *zone;
  u8 unusedRow;
  u8 unusedCol;

  if (gMonEffect.id != ELEMENTAL_HERO_PLASMA_VICE)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  return FindFirstTarget(&unusedRow, &unusedCol);
}

void TrySelectElementalHeroPlasmaViceTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsValidTarget(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  DestroyTarget(targetRow, targetCol);

  gDuelCursor.state = 0;
  gDuelCursor.currentY = gDuelCursor.destY;
  gDuelCursor.currentX = gDuelCursor.destX;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void CancelElementalHeroPlasmaViceTargeting(void)
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

void ActivateElementalHeroPlasmaViceEffect(void)
{
  u8 originRow = gMonEffect.row;
  u8 originCol = gMonEffect.zone;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_PLASMA_VICE, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (!DiscardCostCard())
    return;

  if (WhoseTurn() == DUEL_PLAYER) {
    BeginDestroyTargeting(originRow, originCol);
    return;
  }

  ResolveEffectForAi(originRow, originCol);
}
