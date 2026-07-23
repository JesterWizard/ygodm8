#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "god_card.h"
#include "harpie_conductor.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sHarpieConductorInit APPEND_DATA = {0};
static u8 sConductorProtectOptUsed APPEND_DATA = {0};
static u8 sConductorProtectBusy APPEND_DATA = {0};
static const char sHarpieName[] APPEND_RODATA = "Harpie";

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 ControllerHasFaceUpConductor(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id == HARPIE_CONDUCTOR
        && (IsCardFaceUp(zone) || zone->isDefending == FALSE))
      return TRUE;
  }

  return FALSE;
}

static u8 IsHarpieMonsterId(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 IsLikelySpecialSummonedOpp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsValidBounceTargetFor(u8 controller, u8 fixedRow, u8 fixedCol)
{
  u8 oppMonsterRow;
  u8 turnDuelist;

  turnDuelist = TurnDuelistForFixed(controller);
  oppMonsterRow = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST_MONSTER_ROW
                                                : ACTIVE_DUELIST_MONSTER_ROW;

  if (fixedRow != oppMonsterRow)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST
                                                                   : ACTIVE_DUELIST])
      < 0)
    return FALSE;

  return IsLikelySpecialSummonedOpp(gFixedZones[fixedRow][fixedCol]);
}

static u8 FieldHasBounceTargetFor(u8 controller)
{
  u8 turnDuelist = TurnDuelistForFixed(controller);
  u8 oppMonsterRow = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST_MONSTER_ROW
                                                   : ACTIVE_DUELIST_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidBounceTargetFor(controller, oppMonsterRow, col))
      return TRUE;
  }

  return FALSE;
}

/* Destroy 1 Spell/Trap you control as replacement cost. Auto-pick first. */
static u8 TryDestroyOwnSpellTrap(u8 controller)
{
  u8 turnDuelist = TurnDuelistForFixed(controller);
  u8 backrow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_BACKROW
                                             : INACTIVE_DUELIST_BACKROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[backrow][col];
    u8 typeGroup;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    typeGroup = GetTypeGroup(zone->id);
    if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP
        && typeGroup != TYPE_GROUP_RITUAL)
      continue;

    Duel_DestroyZone(zone, turnDuelist, FALSE);
    return TRUE;
  }

  return FALSE;
}

static u8 TryProtectHarpieWithCost(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 controller;

  if (sConductorProtectBusy || sConductorProtectOptUsed)
    return FALSE;
  if (zone == NULL || zone->id == CARD_NONE || !IsHarpieMonsterId(zone->id))
    return FALSE;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  controller = Duel_FixedDuelistForMonsterRow(fixedRow);
  if (!ControllerHasFaceUpConductor(controller))
    return FALSE;
  if (!TryDestroyOwnSpellTrap(controller))
    return FALSE;

  sConductorProtectBusy = TRUE;
  Duel_ShowEffectTextTyped(HARPIE_CONDUCTOR, 3);
  sConductorProtectOptUsed = TRUE;
  sConductorProtectBusy = FALSE;
  UpdateDuelGfxExceptField();
  return TRUE;
}

u8 HarpieConductor_TryProtectHarpie(struct DuelCard *zone)
{
  return TryProtectHarpieWithCost(zone);
}

u8 HarpieConductor_PreventsBattleDestroy(struct DuelCard *zone)
{
  return TryProtectHarpieWithCost(zone);
}

void HarpieConductor_ClearOnTurnBoundary(void)
{
  sConductorProtectOptUsed = FALSE;
}

static void TryBounceOppOnHarpieReturn(u8 controller)
{
  u8 turnDuelist = TurnDuelistForFixed(controller);
  u8 oppMonsterRow = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST_MONSTER_ROW
                                                   : ACTIVE_DUELIST_MONSTER_ROW;
  u8 col;

  if (EffectOpt_IsUsed(HARPIE_CONDUCTOR))
    return;

  if (!ControllerHasFaceUpConductor(controller))
    return;

  if (!FieldHasBounceTargetFor(controller))
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;

    if (!IsValidBounceTargetFor(controller, oppMonsterRow, col))
      continue;

    zone = gFixedZones[oppMonsterRow][col];
    Duel_ShowEffectTextTyped(HARPIE_CONDUCTOR, 4);
    if (Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) != DUEL_ACTION_OK)
      return;

    EffectOpt_MarkUsed(HARPIE_CONDUCTOR);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }
}

void HarpieConductor_OnHarpieReturned(u8 controller, u16 cardId)
{
  if (controller > DUEL_OPPONENT || cardId == CARD_NONE)
    return;
  if (cardId == HARPIE_CONDUCTOR || !IsHarpieMonsterId(cardId))
    return;

  /* ponytail: Damage Step not detected — may fire on battle-return paths. */
  TryBounceOppOnHarpieReturn(controller);
}

/* Fallback when leave-field fires without ReturnMonsterZone hook. */
static void OnOtherHarpieLeaveWhileConductor(const struct EffectEvent *ev)
{
  if (ev == NULL || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (ev->cardId == HARPIE_CONDUCTOR || !IsHarpieMonsterId(ev->cardId))
    return;

  TryBounceOppOnHarpieReturn(ev->controller);
}

void HarpieConductor_EnsureInit(void)
{
  if (sHarpieConductorInit)
    return;

  sHarpieConductorInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnOtherHarpieLeaveWhileConductor);
}

unsigned char CanActivateHARPIE_CONDUCTOR(void)
{
  /* Destroy-replace via HarpieConductor_TryProtectHarpie; bounce via return hook. */
  return FALSE;
}

void ActivateHARPIE_CONDUCTOREffect(void)
{
}
