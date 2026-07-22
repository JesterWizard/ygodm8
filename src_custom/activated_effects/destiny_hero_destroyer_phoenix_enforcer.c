#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  u8 fixedOwner;

  if (fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW)
    fixedOwner = DUEL_PLAYER;
  else
    fixedOwner = DUEL_OPPONENT;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedOwner])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 IsOwnFieldCard(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ACTIVE_DUELIST_MONSTER_ROW && fixedRow != ACTIVE_DUELIST_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 IsAnyFieldCard(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow > PLAYER_BACKROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 FieldHasOwnCard(void)
{
  u8 row;
  u8 col;

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOwnFieldCard(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 FieldHasOtherCardBesides(u8 skipRow, u8 skipCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (row == skipRow && col == skipCol)
        continue;

      if (IsAnyFieldCard(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 DestroyBestOtherFieldCard(u8 skipRow, u8 skipCol)
{
  u8 row;
  u8 col;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;
  u16 bestScore = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 score;

      if (row == skipRow && col == skipCol)
        continue;

      if (!IsAnyFieldCard(row, col))
        continue;

      zone = gFixedZones[row][col];
      if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
        score = gCardData_NEW[zone->id].atk + 100;
      else
        score = 50;

      /* Prefer opponent cards when scores tie. */
      if (row == INACTIVE_DUELIST_MONSTER_ROW || row == INACTIVE_DUELIST_BACKROW)
        score += 50;

      if (bestRow == 0xFF || score > bestScore) {
        bestScore = score;
        bestRow = row;
        bestCol = col;
      }
    }
  }

  if (bestRow == 0xFF)
    return FALSE;

  if (Duel_DestroyZone(gFixedZones[bestRow][bestCol], TurnDuelistForFixedRow(bestRow), TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  return TRUE;
}

static void ResolveOwnTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOwnFieldCard(fixedRow, fixedCol) || zone == NULL)
    return;

  if (!FieldHasOtherCardBesides(fixedRow, fixedCol))
    return;

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  /* Ceiling: second target picker not chained; auto-destroy best remaining card. */
  DestroyBestOtherFieldCard(0xFF, 0xFF);

  NotifyDynamicEquipFieldChanged();

  if (self != NULL && self->id == DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickOwnTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  u16 bestAtk = 0xFFFF;
  u8 bestRow = 0xFF;
  u8 bestCol = 0xFF;

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!IsOwnFieldCard(row, col))
        continue;

      if (!FieldHasOtherCardBesides(row, col))
        continue;

      zone = gFixedZones[row][col];
      if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
        atk = gCardData_NEW[zone->id].atk;
      else
        atk = 0;

      if (bestRow == 0xFF || atk < bestAtk) {
        bestAtk = atk;
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

unsigned char CanActivateDESTINY_HERO_DESTROYER_PHOENIX_ENFORCER(void)
{
  struct DuelCard *zone;
  u8 row;
  u8 col;

  if (gMonEffect.id != DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER)
    return FALSE;

  /* Ceiling: Quick destroy + GY revive + continuous ATK loss need quick/GY/
   * permanent hooks. Ceiling: OPT destroy 1 you control + 1 other field card. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!FieldHasOwnCard())
    return FALSE;

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOwnFieldCard(row, col) && FieldHasOtherCardBesides(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

void ActivateDESTINY_HERO_DESTROYER_PHOENIX_ENFORCEREffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOwnFieldCard, ResolveOwnTarget, CancelTargeting, AiPickOwnTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
