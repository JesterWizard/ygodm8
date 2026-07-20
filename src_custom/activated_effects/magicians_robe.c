#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static u8 IsHandSpellTrap(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 HandHasSpellTrap(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsHandSpellTrap(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static s8 FindHandSpellTrapZone(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsHandSpellTrap(gTurnHands[ACTIVE_DUELIST][i]->id))
      return (s8)i;
  }

  return -1;
}

static u8 HasDarkMagicianInDeck(void)
{
  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, DARK_MAGICIAN) >= 0;
}

unsigned char CanActivateMAGICIANS_ROBE(void)
{
  if (gMonEffect.id != MAGICIANS_ROBE)
    return FALSE;

  /* ponytail: opp-turn quick + GY SS banish-on-leave need phase/GY hooks.
   * Ceiling: discard S/T from hand → SS DM from Deck via FromHand path. */
  return FALSE;
}

void ActivateMAGICIANS_ROBEEffect(void)
{
  Duel_ShowEffectTextTyped(MAGICIANS_ROBE, 2);
}

u8 CanActivateMagiciansRobeFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != MAGICIANS_ROBE)
    return FALSE;

  /* ponytail: opponent's turn gate not wired. */
  if (!HandHasSpellTrap())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HasDarkMagicianInDeck();
}

u8 TryActivateMagiciansRobeFromHand(u8 handZone)
{
  struct DuelSummonOpts opts;
  s8 spellTrapZone;

  if (!CanActivateMagiciansRobeFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(MAGICIANS_ROBE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  spellTrapZone = FindHandSpellTrapZone();
  if (spellTrapZone < 0)
    return FALSE;

  if (Duel_DestroyZone(gTurnHands[ACTIVE_DUELIST][spellTrapZone], ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, DARK_MAGICIAN, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateMagiciansRobeFromHand(u8 handZone);
u8 TryActivateMagiciansRobeFromHand(u8 handZone);
#endif
