#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sBounceRemaining APPEND_DATA = {0};

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

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

  return count;
}

static u8 IsOppSpellTrapZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 typeGroup;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasBounceTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 BounceOpponentCardToHand(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  s8 empty;
  u16 cardId;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (empty < 0)
    return FALSE;

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
    return Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK;

  if (!IsOppSpellTrapZone(fixedRow, fixedCol))
    return FALSE;

  cardId = zone->id;
  ClearZone(zone);
  InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);
  return TRUE;
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

  return FALSE;
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  sBounceRemaining = 0;
}

static void FinishBrionac(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  sBounceRemaining = 0;
  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void BeginBouncePick(void);

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidTarget(fixedRow, fixedCol))
    return;

  if (!BounceOpponentCardToHand(fixedRow, fixedCol))
    return;

  NotifyDynamicEquipFieldChanged();

  if (sBounceRemaining > 0)
    sBounceRemaining--;

  if (sBounceRemaining > 0 && IsDuelOver() != TRUE && FieldHasBounceTarget()) {
    BeginBouncePick();
    return;
  }

  FinishBrionac();
}

static void BeginBouncePick(void)
{
  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

unsigned char CanActivateBRIONAC_DRAGON_OF_THE_ICE_BARRIER(void)
{
  struct DuelCard *zone;
  u8 discardCount;

  if (gMonEffect.id != BRIONAC_DRAGON_OF_THE_ICE_BARRIER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BRIONAC_DRAGON_OF_THE_ICE_BARRIER)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  discardCount = ComputeDiscardCount();
  return discardCount > 0 && Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) > 0
      && CountOpponentCards() > 0;
}

void ActivateBRIONAC_DRAGON_OF_THE_ICE_BARRIEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 discardCount = ComputeDiscardCount();

  Duel_ShowEffectTextTyped(BRIONAC_DRAGON_OF_THE_ICE_BARRIER, 2);

  if (self == NULL || IsDuelOver() == TRUE || discardCount == 0)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, discardCount, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  sBounceRemaining = discardCount;
  BeginBouncePick();
}
