#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static u8 IsMachineMonster(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER
      && Duel_CardHasMonsterType(cardId, TYPE_MACHINE);
}

static u8 IsBeastWarriorMonster(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER
      && Duel_CardHasMonsterType(cardId, TYPE_BEAST_WARRIOR);
}

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 HandHasTypeExcludingSlot(u8 handZone, u8 (*pred)(u16))
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (i == handZone)
      continue;

    if (pred(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasType(u8 (*pred)(u16))
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && pred(zone->id))
      return TRUE;
  }

  return FALSE;
}

static u8 GyHasType(u8 fixedDuelist, u8 (*pred)(u16))
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return pred(gDuel.duelistbattleState[fixedDuelist].graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (pred(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 HasTypeAccessible(u8 handZone, u8 (*pred)(u16))
{
  u8 fixedDuelist = FixedDuelistForActive();

  return HandHasTypeExcludingSlot(handZone, pred) || FieldHasType(pred)
      || GyHasType(fixedDuelist, pred);
}

static u8 BanishHandSlot(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= MAX_ZONES_IN_ROW)
    return FALSE;

  return Duel_BanishZone(SixCardHand_ZoneAtHandRow(handRow, handZone), TRUE) != DUEL_ACTION_DUEL_OVER;
}

static u8 BanishOneType(u8 handZone, u8 (*pred)(u16))
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (i == handZone)
      continue;

    if (pred(gTurnHands[ACTIVE_DUELIST][i]->id))
      return BanishHandSlot(i);
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone != NULL && pred(zone->id)) {
      if (Duel_BanishZone(zone, TRUE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;
      return TRUE;
    }
  }

  if (!GraveyardExpand_IsEnabled()) {
    if (pred(gDuel.duelistbattleState[fixedDuelist].graveyard)) {
      Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
      return TRUE;
    }
    return FALSE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (pred(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
      return Duel_BanishGraveyardAtFixed(fixedDuelist, i) != CARD_NONE;
    }
  }

  return FALSE;
}

unsigned char CanActivateBEAST_MACHINE_KING_BARBAROS_UR(void)
{
  if (gMonEffect.id != BEAST_MACHINE_KING_BARBAROS_UR)
    return FALSE;

  /* ponytail: no battle damage to opp when this card battles needs battle hook.
   * Ceiling: not field-ignition activatable; SS-from-hand uses FromHand path. */
  return FALSE;
}

void ActivateBEAST_MACHINE_KING_BARBAROS_UREffect(void)
{
  Duel_ShowEffectTextTyped(BEAST_MACHINE_KING_BARBAROS_UR, 2);
}

u8 CanSpecialSummonBeastMachineKingBarbarosUrFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != BEAST_MACHINE_KING_BARBAROS_UR)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  /* ponytail: multi-zone banish picker not wired; require both types reachable. */
  return HasTypeAccessible(handZone, IsMachineMonster)
      && HasTypeAccessible(handZone, IsBeastWarriorMonster);
}

u8 TrySpecialSummonBeastMachineKingBarbarosUrFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 barbarosZone;

  if (!CanSpecialSummonBeastMachineKingBarbarosUrFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(BEAST_MACHINE_KING_BARBAROS_UR, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!BanishOneType(handZone, IsMachineMonster) || IsDuelOver() == TRUE)
    return FALSE;

  if (!BanishOneType(handZone, IsBeastWarriorMonster) || IsDuelOver() == TRUE)
    return FALSE;

  barbarosZone = (s8)handZone;
  if (SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], handZone)->id
      != BEAST_MACHINE_KING_BARBAROS_UR) {
    u8 i;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (gTurnHands[ACTIVE_DUELIST][i]->id == BEAST_MACHINE_KING_BARBAROS_UR) {
        barbarosZone = (s8)i;
        break;
      }
    }
  }

  if (barbarosZone < 0)
    return FALSE;

  return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, barbarosZone, opts) == DUEL_ACTION_OK;
}
