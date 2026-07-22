#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 IsGravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGravekeepersName);
}

static u8 IsFaceUpMonsterZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  /* Attack-position summons stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 OpponentMonsterRow(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return OPPONENT_MONSTER_ROW;

  return PLAYER_MONSTER_ROW;
}

static u8 OpponentBackrow(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return OPPONENT_BACKROW;

  return PLAYER_BACKROW;
}

static u8 TurnDuelistOwningFixedRow(u8 fixedRow)
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

static u8 IsValidTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != gMonEffect.row)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || zone->id == GRAVEKEEPERS_DESCENDANT)
    return FALSE;

  if (!IsGravekeeperMonster(zone->id) || !IsFaceUpMonsterZone(zone))
    return FALSE;

  return TRUE;
}

static u8 IsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OpponentMonsterRow() && fixedRow != OpponentBackrow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE;
}

static u8 FieldHasTributeTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTributeTarget(gMonEffect.row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasDestroyTarget(void)
{
  u8 row;
  u8 col;

  for (row = OpponentMonsterRow(); row <= OpponentBackrow(); row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidDestroyTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void BeginDestroyTargetPick(void);

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidDestroyTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(fixedRow), FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (self != NULL)
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

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OpponentMonsterRow(); row <= OpponentBackrow(); row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidDestroyTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static void BeginDestroyTargetPick(void)
{
  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidDestroyTarget, ResolveDestroyTarget, CancelTargeting,
                     AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static void ResolveTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidTributeTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE || !FieldHasDestroyTarget())
    return;

  BeginDestroyTargetPick();
}

static u8 AiPickTributeTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTributeTarget(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateGRAVEKEEPERS_DESCENDANT(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRAVEKEEPERS_DESCENDANT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRAVEKEEPERS_DESCENDANT)
    return FALSE;

  return CanUseMonsterEffect(zone) && FieldHasTributeTarget() && FieldHasDestroyTarget();
}

void ActivateGRAVEKEEPERS_DESCENDANTEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_DESCENDANT, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTributeTarget, ResolveTributeTarget, CancelTargeting,
                     AiPickTributeTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
