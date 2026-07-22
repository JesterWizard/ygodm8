#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  u8 fixedOwner;

  if (fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW)
    fixedOwner = DUEL_PLAYER;
  else
    fixedOwner = DUEL_OPPONENT;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedOwner])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 IsFaceUpMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 CountFaceUpMonstersOnField(void)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpMonster(gFixedZones[row][col]))
        count++;
    }
  }

  return count;
}

static void TributeAllFaceUpMonsters(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 gy = TurnDuelistForFixedRow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (!IsFaceUpMonster(zone))
        continue;

      if (Duel_DestroyZone(zone, gy, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }

  NotifyDynamicEquipFieldChanged();
}

unsigned char CanActivateNIBIRU_THE_PRIMAL_BEING(void)
{
  if (gMonEffect.id != NIBIRU_THE_PRIMAL_BEING)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * FromHand wipe+SS if ≥5 face-up monsters on field. */
  return FALSE;
}

u8 CanSpecialSummonNibiruThePrimalBeingFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != NIBIRU_THE_PRIMAL_BEING)
    return FALSE;

  if (CountFaceUpMonstersOnField() < 5)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return TRUE;
}

u8 TrySpecialSummonNibiruThePrimalBeingFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonNibiruThePrimalBeingFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(NIBIRU_THE_PRIMAL_BEING, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  TributeAllFaceUpMonsters();

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

void ActivateNIBIRU_THE_PRIMAL_BEINGEffect(void)
{
  Duel_ShowEffectTextTyped(NIBIRU_THE_PRIMAL_BEING, 2);
}

#if !defined(__GNUC__)
u8 CanSpecialSummonNibiruThePrimalBeingFromHand(u8 handZone);
u8 TrySpecialSummonNibiruThePrimalBeingFromHand(u8 handZone);
#endif
