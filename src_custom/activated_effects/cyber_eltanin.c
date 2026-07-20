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

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 IsLightMachine(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_LIGHT
      && Duel_CardHasMonsterType(cardId, TYPE_MACHINE);
}

static u8 BanishLightMachineZone(struct DuelCard *zone, u8 *banishedCount)
{
  if (zone == NULL || zone->id == CARD_NONE || !IsLightMachine(zone->id))
    return TRUE;

  if (Duel_BanishZone(zone, FALSE) == DUEL_ACTION_DUEL_OVER)
    return FALSE;

  (*banishedCount)++;
  return TRUE;
}

static u8 BanishAllLightMachinesFromFieldAndGy(u8 *banishedCount)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 col;
  u8 i;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!BanishLightMachineZone(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col], banishedCount))
      return FALSE;
  }

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsLightMachine(cardId)) {
      Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
      (*banishedCount)++;
    }

    return TRUE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsLightMachine(cardId))
      continue;

    if (Duel_BanishGraveyardAtFixed(fixedDuelist, i) == CARD_NONE)
      return FALSE;

    (*banishedCount)++;
    i--;
  }

  return TRUE;
}

static void SendOtherFaceUpMonstersToGy(struct DuelCard *self)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == self || zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
        continue;

      if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
        continue;

      if (Duel_DestroyZone(zone, TurnDuelistForFixedRow(row), FALSE) == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }

  NotifyDynamicEquipFieldChanged();
}

unsigned char CanActivateCYBER_ELTANIN(void)
{
  if (gMonEffect.id != CYBER_ELTANIN)
    return FALSE;

  /* ponytail: continuous ATK/DEF = banished×500 needs permanent overlay hook.
   * Ceiling: not field-ignition activatable; use FromHand banish path. */
  return FALSE;
}

void ActivateCYBER_ELTANINEffect(void)
{
  Duel_ShowEffectTextTyped(CYBER_ELTANIN, 2);
}

u8 CanSpecialSummonCyberEltaninFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != CYBER_ELTANIN)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonCyberEltaninFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *self;
  u8 banished = 0;
  u8 stages;

  if (!CanSpecialSummonCyberEltaninFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(CYBER_ELTANIN, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!BanishAllLightMachinesFromFieldAndGy(&banished) || IsDuelOver() == TRUE)
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  self = NULL;
  {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

      if (zone != NULL && zone->id == CYBER_ELTANIN) {
        self = zone;
        break;
      }
    }
  }

  stages = banished;
  if (stages > 20)
    stages = 20;

  if (self != NULL) {
    /* ponytail: permStage unit is ~500 ATK/DEF each, not exact banished×500 overlay. */
    SetPermStage(self, stages);
    SendOtherFaceUpMonstersToGy(self);
  }

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonCyberEltaninFromHand(u8 handZone);
u8 TrySpecialSummonCyberEltaninFromHand(u8 handZone);
#endif
