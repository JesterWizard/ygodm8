#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAncientGearMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == ANCIENT_GEAR_TANKER)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u8 OppHasMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id != CARD_NONE
        && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      return TRUE;
  }

  return FALSE;
}

static s8 FindAncientGearHandZone(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (slot != NULL && IsAncientGearMonster(slot->id)
        && !Duel_CardCannotBeSpecialSummoned(slot->id))
      return (s8)i;
  }

  return -1;
}

static u16 FindAncientGearInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsAncientGearMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId)
        ? cardId
        : CARD_NONE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsAncientGearMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanSpecialSummonAncientGear(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (FindAncientGearHandZone() >= 0)
    return TRUE;

  if (OppHasMonster() && FindAncientGearInGy() != CARD_NONE)
    return TRUE;

  return FALSE;
}

static u8 SpecialSummonAncientGear(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 handZone;
  u8 fixedDuelist = FixedDuelistForActive();
  u16 gyId;
  u8 i;

  handZone = FindAncientGearHandZone();
  if (handZone >= 0)
    return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)handZone, opts) == DUEL_ACTION_OK;

  if (!OppHasMonster())
    return FALSE;

  gyId = FindAncientGearInGy();
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

static u8 IsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  struct DuelCard *self;

  if (fixedRow != ACTIVE_DUELIST_MONSTER_ROW && fixedRow != ACTIVE_DUELIST_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == self)
    return FALSE;

  return IsCardFaceUp(zone)
      || (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER && zone->isDefending == FALSE);
}

static u8 FieldHasDestroyTarget(void)
{
  u8 row;
  u8 col;

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidDestroyTarget(row, col))
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

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  /* ponytail: AG pierce mark for rest of turn FALSE. */
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

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_BACKROW; row++) {
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

unsigned char CanActivateANCIENT_GEAR_TANKER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_TANKER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_TANKER)
    return FALSE;

  /* ponytail: pierce mark AG monsters FALSE.
   * Ceiling: OPT SS AG from hand (GY if opp has monster), else OPT destroy your face-up.
   * Separate OPTs share one MarkMonsterEffectUsed. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (CanSpecialSummonAncientGear())
    return TRUE;

  return FieldHasDestroyTarget();
}

void ActivateANCIENT_GEAR_TANKEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_TANKER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CanSpecialSummonAncientGear()) {
    if (!SpecialSummonAncientGear())
      return;

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (!FieldHasDestroyTarget())
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
