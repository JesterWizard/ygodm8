#include "global.h"
#include "common-chax.h"
#include "ancient_gear_megaton_golem.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sMegatonInit APPEND_DATA = {0};

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

static u8 IsAncientGearGolem(u16 cardId)
{
  return cardId == ANCIENT_GEAR_GOLEM || cardId == ANCIENT_GEAR_GOLEM_ULTIMATE_POUND
      || cardId == ULTIMATE_ANCIENT_GEAR_GOLEM;
}

static s8 FindGolemHandZone(u8 turnDuelist)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], i);

    if (slot != NULL && IsAncientGearGolem(slot->id)
        && !Duel_CardCannotBeSpecialSummoned(slot->id))
      return (s8)i;
  }

  return -1;
}

static s8 FindBasicGolemHandZone(u8 turnDuelist)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], i);

    if (slot != NULL && slot->id == ANCIENT_GEAR_GOLEM
        && !Duel_CardCannotBeSpecialSummoned(slot->id))
      return (s8)i;
  }

  return -1;
}

static u16 FindGolemInGy(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsAncientGearGolem(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId)
        ? cardId
        : CARD_NONE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsAncientGearGolem(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanSsGolem(void)
{
  u8 fixedDuelist = FixedDuelistForActive();

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (FindGolemHandZone(ACTIVE_DUELIST) >= 0)
    return TRUE;

  return FindGolemInGy(fixedDuelist) != CARD_NONE;
}

static u8 SpecialSummonGolem(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 handZone;
  u8 fixedDuelist = FixedDuelistForActive();
  u16 gyId;
  u8 i;

  handZone = FindGolemHandZone(ACTIVE_DUELIST);
  if (handZone >= 0)
    return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)handZone, opts) == DUEL_ACTION_OK;

  gyId = FindGolemInGy(fixedDuelist);
  if (gyId == CARD_NONE)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts) == DUEL_ACTION_OK;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) != gyId)
      continue;

    gyId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, gyId, opts) == DUEL_ACTION_OK;
  }

  return FALSE;
}

/* Extra Deck Ultimate AG Golem SS blocked — AG Golem from hand/GY/Deck instead. */
static void TrySsAncientGearGolemOnLeave(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                                : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts;
  s8 handZone;
  u8 ok = FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;

  handZone = FindBasicGolemHandZone(turnDuelist);
  if (handZone < 0 && FindGolemInGy(fixedDuelist) != ANCIENT_GEAR_GOLEM
      && Duel_FindDeckCardIndex(turnDuelist, ANCIENT_GEAR_GOLEM) < 0)
    return;

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_MEGATON_GOLEM, 8);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (handZone >= 0)
    ok = Duel_SpecialSummonFromHandZone(turnDuelist, (u8)handZone, opts) == DUEL_ACTION_OK;
  if (!ok)
    ok = Duel_SpecialSummonFromGrave(turnDuelist, ANCIENT_GEAR_GOLEM, opts) == DUEL_ACTION_OK;
  if (!ok && Duel_FindDeckCardIndex(turnDuelist, ANCIENT_GEAR_GOLEM) >= 0)
    ok = Duel_SpecialSummonFromDeck(turnDuelist, ANCIENT_GEAR_GOLEM, opts) == DUEL_ACTION_OK;
  if (!ok)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void OnMegatonLeaveField(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != ANCIENT_GEAR_MEGATON_GOLEM || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;

  TrySsAncientGearGolemOnLeave(ev->controller);
}

void AncientGearMegatonGolem_EnsureInit(void)
{
  if (sMegatonInit)
    return;

  sMegatonInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnMegatonLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnMegatonLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnMegatonLeaveField);
}

unsigned char CanActivateANCIENT_GEAR_MEGATON_GOLEM(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_MEGATON_GOLEM)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_MEGATON_GOLEM)
    return FALSE;

  /* OPT SS AG Golem from hand/GY. Pierce via ApplyAncientGearGolemPiercingBattleEffect.
   * Leave → AG Golem hand/GY/Deck via AncientGearMegatonGolem_EnsureInit
   * (Extra Deck Ultimate blocked). multi-attack. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanSsGolem();
}

void ActivateANCIENT_GEAR_MEGATON_GOLEMEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_MEGATON_GOLEM, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!SpecialSummonGolem())
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
