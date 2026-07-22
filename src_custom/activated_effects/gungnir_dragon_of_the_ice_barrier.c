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

static u8 sDestroyRemaining APPEND_DATA = {0};

static u8 CountOpponentCards(void)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE && !IsGodCard(zone->id))
        count++;
    }
  }

  return count;
}

static u8 ComputeDiscardCount(void)
{
  u8 handCount = Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]);
  u8 oppCount = CountOpponentCards();
  u8 count = handCount;

  if (oppCount < count)
    count = oppCount;
  if (count > 2)
    count = 2;

  return count;
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

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != OPPONENT_BACKROW
      && fixedRow != PLAYER_MONSTER_ROW && fixedRow != PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasDestroyTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (row = PLAYER_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  sDestroyRemaining = 0;
}

static void FinishGungnir(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  sDestroyRemaining = 0;
  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void BeginDestroyPick(void);

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(fixedRow), FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (sDestroyRemaining > 0)
    sDestroyRemaining--;

  if (sDestroyRemaining > 0 && IsDuelOver() != TRUE && FieldHasDestroyTarget()) {
    BeginDestroyPick();
    return;
  }

  FinishGungnir();
}

static void BeginDestroyPick(void)
{
  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

unsigned char CanActivateGUNGNIR_DRAGON_OF_THE_ICE_BARRIER(void)
{
  struct DuelCard *zone;
  u8 discardCount;

  if (gMonEffect.id != GUNGNIR_DRAGON_OF_THE_ICE_BARRIER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GUNGNIR_DRAGON_OF_THE_ICE_BARRIER)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  discardCount = ComputeDiscardCount();
  return discardCount > 0 && Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) > 0
      && FieldHasDestroyTarget();
}

void ActivateGUNGNIR_DRAGON_OF_THE_ICE_BARRIEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 discardCount = ComputeDiscardCount();

  Duel_ShowEffectTextTyped(GUNGNIR_DRAGON_OF_THE_ICE_BARRIER, 2);

  if (self == NULL || IsDuelOver() == TRUE || discardCount == 0)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, discardCount, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  sDestroyRemaining = discardCount;
  BeginDestroyPick();
}
