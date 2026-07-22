#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static u8 IsFiendMonster(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER
      && Duel_CardHasMonsterType(cardId, TYPE_FIEND);
}

static u8 FieldHasFiendExcludingHandSlot(u8 handZone)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsFiendMonster(zone->id))
      return TRUE;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (col == handZone)
      continue;

    if (IsFiendMonster(gTurnHands[ACTIVE_DUELIST][col]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 SendFieldFiendToGy(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || !IsFiendMonster(zone->id))
      continue;

    if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return FALSE;

    return TRUE;
  }

  return FALSE;
}

static u8 SendHandFiendToGy(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *slot;

    if (col == handZone)
      continue;

    slot = SixCardHand_ZoneAtHandRow(handRow, col);
    if (!IsFiendMonster(slot->id))
      continue;

    if (Duel_DestroyZone(slot, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return FALSE;

    return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateDARKNESS_NEOSPHERE(void)
{
  if (gMonEffect.id != DARKNESS_NEOSPHERE)
    return FALSE;

  /* Ceiling: battle indestruct + trap bounce + attack-declare gate need battle/
   * phase hooks. Ceiling: not field-ignition activatable; SS uses FromHand path. */
  return FALSE;
}

void ActivateDARKNESS_NEOSPHEREEffect(void)
{
  Duel_ShowEffectTextTyped(DARKNESS_NEOSPHERE, 2);
}

u8 CanSpecialSummonDarknessNeosphereFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != DARKNESS_NEOSPHERE)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  /* Ceiling: opp attack declare gate not wired; require 1 field + 1 hand Fiend. */
  return FieldHasFiendExcludingHandSlot(handZone);
}

u8 TrySpecialSummonDarknessNeosphereFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonDarknessNeosphereFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DARKNESS_NEOSPHERE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!SendFieldFiendToGy())
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!SendHandFiendToGy(handZone))
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonDarknessNeosphereFromHand(u8 handZone);
u8 TrySpecialSummonDarknessNeosphereFromHand(u8 handZone);
#endif
