#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAncientGearGolem(u16 cardId)
{
  return cardId == ANCIENT_GEAR_GOLEM || cardId == ANCIENT_GEAR_GOLEM_ULTIMATE_POUND
      || cardId == ULTIMATE_ANCIENT_GEAR_GOLEM;
}

static s8 FindGolemHandZone(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (slot != NULL && IsAncientGearGolem(slot->id)
        && !Duel_CardCannotBeSpecialSummoned(slot->id))
      return (s8)i;
  }

  return -1;
}

static u16 FindGolemInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
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
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (FindGolemHandZone() >= 0)
    return TRUE;

  return FindGolemInGy() != CARD_NONE;
}

static u8 SpecialSummonGolem(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 handZone;
  u8 fixedDuelist = FixedDuelistForActive();
  u16 gyId;
  u8 i;

  handZone = FindGolemHandZone();
  if (handZone >= 0)
    return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)handZone, opts) == DUEL_ACTION_OK;

  gyId = FindGolemInGy();
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

unsigned char CanActivateANCIENT_GEAR_MEGATON_GOLEM(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_MEGATON_GOLEM)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_MEGATON_GOLEM)
    return FALSE;

  /* ponytail: multi-attack + leave-field SS FALSE.
   * Ceiling: OPT SS AG Golem from hand/GY. */
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
