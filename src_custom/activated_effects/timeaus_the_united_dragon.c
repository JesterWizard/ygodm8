#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyardDuelist);
void UpdateDuelGfxExceptField(void);

static const char sDarkMagicianName[] APPEND_RODATA = "Dark Magician";

static u8 IsSpellcasterMonster(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER
      && Duel_CardHasMonsterType(cardId, TYPE_SPELLCASTER);
}

static u8 IsDarkMagicianMentionSpellTrap(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sDarkMagicianName);
}

static u8 IsValidSendCost(u16 cardId)
{
  return IsSpellcasterMonster(cardId) || IsDarkMagicianMentionSpellTrap(cardId);
}

static u8 HandHasSendCost(u8 timeausHandZone)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 cardId;

    if (col == timeausHandZone)
      continue;

    cardId = gTurnHands[ACTIVE_DUELIST][col]->id;
    if (IsValidSendCost(cardId))
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasFaceUpSendCost(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id != CARD_NONE && IsSpellcasterMonster(zone->id)
        && (IsCardFaceUp(zone) || zone->isDefending == FALSE))
      return TRUE;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (zone != NULL && zone->id != CARD_NONE && IsDarkMagicianMentionSpellTrap(zone->id)
        && IsCardFaceUp(zone))
      return TRUE;
  }

  return FALSE;
}

static s8 FindHandSendCostZone(u8 timeausHandZone)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 cardId;

    if (col == timeausHandZone)
      continue;

    cardId = gTurnHands[ACTIVE_DUELIST][col]->id;
    if (IsValidSendCost(cardId))
      return (s8)col;
  }

  return -1;
}

static u8 SendFirstAvailableCost(u8 timeausHandZone)
{
  s8 handZone;
  u8 col;

  handZone = FindHandSendCostZone(timeausHandZone);
  if (handZone >= 0) {
    struct DuelCard *slot = gTurnHands[ACTIVE_DUELIST][handZone];

    if (GetTypeGroup(slot->id) == TYPE_GROUP_MONSTER)
      ClearZoneAndSendMonToGraveyard(slot, ACTIVE_DUELIST);
    else
      Duel_DestroyZone(slot, ACTIVE_DUELIST, FALSE);

    return TRUE;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id != CARD_NONE && IsSpellcasterMonster(zone->id)
        && (IsCardFaceUp(zone) || zone->isDefending == FALSE)) {
      if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;

      return TRUE;
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (zone != NULL && zone->id != CARD_NONE && IsDarkMagicianMentionSpellTrap(zone->id)
        && IsCardFaceUp(zone)) {
      if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;

      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateTIMEAUS_THE_UNITED_DRAGON(void)
{
  if (gMonEffect.id != TIMEAUS_THE_UNITED_DRAGON)
    return FALSE;

  /* Main Phase Fusion Summon needs fusion UI hook.
   * Ceiling: SS from hand via send cost uses FromHand path. */
  return FALSE;
}

void ActivateTIMEAUS_THE_UNITED_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(TIMEAUS_THE_UNITED_DRAGON, 2);
}

u8 CanSpecialSummonTimeausTheUnitedDragonFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != TIMEAUS_THE_UNITED_DRAGON)
    return FALSE;

  if (!HandHasSendCost(handZone) && !FieldHasFaceUpSendCost())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonTimeausTheUnitedDragonFromHand(u8 handZone)
{
  struct DuelSummonOpts opts;

  if (!CanSpecialSummonTimeausTheUnitedDragonFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(TIMEAUS_THE_UNITED_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!SendFirstAvailableCost(handZone))
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonTimeausTheUnitedDragonFromHand(u8 handZone);
u8 TrySpecialSummonTimeausTheUnitedDragonFromHand(u8 handZone);
#endif
