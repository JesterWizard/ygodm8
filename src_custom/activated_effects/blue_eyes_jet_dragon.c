#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "blue_eyes_jet_dragon.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sJetInit APPEND_DATA = {0};

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

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 BewdOnFieldOrGyFor(u8 fixedDuelist)
{
  u8 monRow = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;
  u8 i;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[monRow][col];

    if (zone != NULL && zone->id == BLUE_EYES_WHITE_DRAGON)
      return TRUE;
  }

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == BLUE_EYES_WHITE_DRAGON;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == BLUE_EYES_WHITE_DRAGON)
      return TRUE;
  }

  return FALSE;
}

static u8 BewdOnFieldOrGy(void)
{
  return BewdOnFieldOrGyFor(FixedDuelistForActive());
}

static s8 FindJetHandZone(u8 turnDuelist)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], i);

    if (slot != NULL && slot->id == BLUE_EYES_JET_DRAGON
        && !Duel_CardCannotBeSpecialSummoned(slot->id))
      return (s8)i;
  }

  return -1;
}

static void TrySsJetFromHandOnBewdDestroy(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u8 monRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                            : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts;
  s8 handZone;

  if (EffectOpt_IsUsed(BLUE_EYES_JET_DRAGON))
    return;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monRow]) < 0)
    return;

  handZone = FindJetHandZone(turnDuelist);
  if (handZone < 0)
    return;

  Duel_ShowEffectTextTyped(BLUE_EYES_JET_DRAGON, 8);
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHandZone(turnDuelist, (u8)handZone, opts) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(BLUE_EYES_JET_DRAGON);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void OnBewdOrAltDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (ev->cardId != BLUE_EYES_WHITE_DRAGON
      && ev->cardId != BLUE_EYES_ALTERNATIVE_WHITE_DRAGON)
    return;

  /* Alt needs a separate BEWD on field/GY; BEWD-destroy still has itself on field
   * during ON_DESTROY emit (pre-ClearZone). */
  if (ev->cardId == BLUE_EYES_ALTERNATIVE_WHITE_DRAGON
      && !BewdOnFieldOrGyFor(ev->controller))
    return;

  TrySsJetFromHandOnBewdDestroy(ev->controller);
}

void BlueEyesJetDragon_EnsureInit(void)
{
  if (sJetInit)
    return;

  sJetInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnBewdOrAltDestroyed);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnBewdOrAltDestroyed);
}

static u8 BounceZoneToOwnerHand(struct DuelCard *zone, u8 ownerTurn)
{
  u8 typeGroup;
  s8 empty;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ownerTurn]) < 0)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  if (typeGroup == TYPE_GROUP_MONSTER)
    return Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK;

  if (typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP) {
    u16 cardId = zone->id;

    empty = FirstEmptyZoneInRow(gTurnHands[ownerTurn]);
    if (empty < 0)
      return FALSE;

    ClearZone(zone);
    InitHandSlotFromCard(gTurnHands[ownerTurn][empty], cardId);
    return TRUE;
  }

  return FALSE;
}

static u8 OwnerTurnForFixedRow(u8 fixedRow)
{
  if (fixedRow == ACTIVE_DUELIST_MONSTER_ROW || fixedRow == ACTIVE_DUELIST_BACKROW)
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 IsValidBounceTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  struct DuelCard *self;

  if (fixedRow != ACTIVE_DUELIST_MONSTER_ROW && fixedRow != ACTIVE_DUELIST_BACKROW
      && fixedRow != INACTIVE_DUELIST_MONSTER_ROW && fixedRow != INACTIVE_DUELIST_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == self)
    return FALSE;

  return FirstEmptyZoneInRow(gTurnHands[OwnerTurnForFixedRow(fixedRow)]) >= 0;
}

static u8 FieldHasBounceTarget(void)
{
  u8 row;
  u8 col;

  for (row = 0; row < 5; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidBounceTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveBounceTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidBounceTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (!BounceZoneToOwnerHand(zone, OwnerTurnForFixedRow(fixedRow)))
    return;

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

static u8 AiPickBounceTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidBounceTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidBounceTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateBLUE_EYES_JET_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BLUE_EYES_JET_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BLUE_EYES_JET_DRAGON)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!BewdOnFieldOrGy())
    return FALSE;

  return FieldHasBounceTarget();
}

void ActivateBLUE_EYES_JET_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(BLUE_EYES_JET_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  Duel_SetupPickZone(IsValidBounceTarget, ResolveBounceTarget, CancelTargeting,
                     AiPickBounceTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

u8 CanSpecialSummonBlueEyesJetDragonFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != BLUE_EYES_JET_DRAGON)
    return FALSE;

  if (!BewdOnFieldOrGy())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonBlueEyesJetDragonFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonBlueEyesJetDragonFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(BLUE_EYES_JET_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonBlueEyesJetDragonFromHand(u8 handZone);
u8 TrySpecialSummonBlueEyesJetDragonFromHand(u8 handZone);
#endif
