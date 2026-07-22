#include "global.h"
#include "aromage_cananga.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(void);
u8 GetDuelistForZone(struct DuelCard *zone);

#define CANANGA_STAT_PENALTY 500

static u8 ControllerHasFaceUpCanangaWithLpAdvantage(u8 oppController)
{
  u8 me = oppController == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 row;
  u8 col;

  if (gDuelLifePoints[me] <= gDuelLifePoints[oppController])
    return FALSE;

  row = Duel_FixedMonsterRowForDuelist(me);
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AROMAGE_CANANGA)
      return TRUE;
  }
  return FALSE;
}

void ApplyAromageCanangaStatPenaltyToCardInfo(const struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return;
  if (!Duel_CardIsMonster(zone->id))
    return;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return;
  if (!ControllerHasFaceUpCanangaWithLpAdvantage(controller))
    return;

  if (gCardInfo.atk > CANANGA_STAT_PENALTY)
    gCardInfo.atk -= CANANGA_STAT_PENALTY;
  else
    gCardInfo.atk = 0;
  if (gCardInfo.def > CANANGA_STAT_PENALTY)
    gCardInfo.def -= CANANGA_STAT_PENALTY;
  else
    gCardInfo.def = 0;
}

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

  if (fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 OppHasSpellTrapWithHandRoom(void)
{
  u8 col;

  if (NumEmptyZonesInRow(gTurnHands[INACTIVE_DUELIST]) == 0)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppSpellTrapZone(OPPONENT_BACKROW, col))
      return TRUE;
  }

  return FALSE;
}

static u8 BounceSpellTrapToHand(struct DuelCard *zone)
{
  s8 empty;
  u16 cardId;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (empty < 0)
    return FALSE;

  cardId = zone->id;
  ClearZone(zone);
  InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], cardId);
  return TRUE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOppSpellTrapZone(fixedRow, fixedCol) || zone == NULL)
    return;

  if (!BounceSpellTrapToHand(zone))
    return;

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = OPPONENT_BACKROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppSpellTrapZone(OPPONENT_BACKROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateAROMAGE_CANANGA(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMAGE_CANANGA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMAGE_CANANGA)
    return FALSE;

  /* Continuous -500 via ApplyAromageCanangaStatPenaltyToCardInfo.
   * Ceiling: LP-gain bounce trigger needs LP hook.
   * Ceiling: OPT bounce 1 opp Spell/Trap if hand room. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OppHasSpellTrapWithHandRoom();
}

void ActivateAROMAGE_CANANGAEffect(void)
{
  Duel_ShowEffectTextTyped(AROMAGE_CANANGA, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOppSpellTrapZone, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
