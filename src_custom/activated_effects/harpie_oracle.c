#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "harpie_perfumer.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static const char sHarpieName[] APPEND_RODATA = "Harpie";

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 ControlsLevel5PlusHarpie(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    u16 cardId;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    cardId = zone->id;
    if (!IsHarpieMonster(cardId))
      continue;

    if (cardId < NUM_TOTAL_CARDS && gCardData_NEW[cardId].level >= 5)
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateHARPIE_ORACLE(void)
{
  /* No field ignition — hand SS + EP GY add only. */
  return FALSE;
}

void ActivateHARPIE_ORACLEEffect(void)
{
  Duel_ShowEffectTextTyped(HARPIE_ORACLE, 2);
}

void TryHarpieOracleOnMonsterPlacement(struct DuelCard *zone, enum DuelSummonMode mode)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  (void)mode;

  if (zone == NULL || zone->id != HARPIE_ORACLE || gHideEffectText)
    return;

  {
    u8 fixedRow;
    u8 col;

    if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
      return;
    fixedDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  }
  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  HarpieOracle_ArmEndPhasePending(turnDuelist);
}

u8 CanSpecialSummonHarpieOracleFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HARPIE_ORACLE)
    return FALSE;

  if (EffectOpt_IsUsed(HARPIE_ORACLE))
    return FALSE;

  if (!ControlsLevel5PlusHarpie())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonHarpieOracleFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonHarpieOracleFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(HARPIE_ORACLE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  EffectOpt_MarkUsed(HARPIE_ORACLE);
  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonHarpieOracleFromHand(u8 handZone);
u8 TrySpecialSummonHarpieOracleFromHand(u8 handZone);
#endif
