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

static u8 OppHasBounceTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER
          || IsOppSpellTrapZone(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 OppHasSpellTrap(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppSpellTrapZone(OPPONENT_BACKROW, col))
      return TRUE;
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

static u8 BounceFirstOpponentCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER
          || IsOppSpellTrapZone(row, col)) {
        if (BounceOpponentCardToHand(row, col))
          return TRUE;
      }
    }
  }

  return FALSE;
}

static u8 IsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  return IsOppSpellTrapZone(fixedRow, fixedCol);
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = OPPONENT_BACKROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidDestroyTarget(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidDestroyTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

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

unsigned char CanActivateSHADDOLL_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SHADDOLL_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SHADDOLL_DRAGON)
    return FALSE;

  /* FLIP vs GY-sent exclusivity + trigger hooks deferred. Ceiling: bounce 1
   * opp card OR destroy 1 opp Spell/Trap once via usage. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OppHasBounceTarget() || OppHasSpellTrap();
}

void ActivateSHADDOLL_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(SHADDOLL_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (OppHasBounceTarget() && NumEmptyZonesInRow(gTurnHands[INACTIVE_DUELIST]) > 0) {
    if (BounceFirstOpponentCard()) {
      MarkMonsterEffectUsed(self);
      UpdateDuelGfxExceptField();
      CheckWinConditionExodia(WhoseTurn());
      if (IsDuelOver() != TRUE)
        TryActivatingPermanentEffects();
    }
    return;
  }

  if (!OppHasSpellTrap())
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidDestroyTarget, ResolveDestroyTarget, CancelTargeting,
                     AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
