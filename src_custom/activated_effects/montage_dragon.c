#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static u8 IsOtherHandMonster(u16 cardId)
{
  return cardId != MONTAGE_DRAGON && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 CountOtherHandMonsters(u8 montageZone)
{
  u8 count = 0;
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (i == montageZone)
      continue;

    if (IsOtherHandMonster(
            SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id))
      count++;
  }

  return count;
}

unsigned char CanActivateMONTAGE_DRAGON(void)
{
  if (gMonEffect.id != MONTAGE_DRAGON)
    return FALSE;

  /* ponytail: ATK = combined sent Levels x 300 needs summon-stat overlay hook.
   * Ceiling: not field-ignition activatable; SS-from-hand uses FromHand path. */
  return FALSE;
}

void ActivateMONTAGE_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(MONTAGE_DRAGON, 2);
}

u8 CanSpecialSummonMontageDragonFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != MONTAGE_DRAGON)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return CountOtherHandMonsters(handZone) >= 3;
}

u8 TrySpecialSummonMontageDragonFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 montageZone;

  if (!CanSpecialSummonMontageDragonFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(MONTAGE_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 3, IsOtherHandMonster, TRUE) != DUEL_ACTION_OK)
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  montageZone = (s8)handZone;
  if (SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], handZone)->id != MONTAGE_DRAGON) {
    u8 i;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (gTurnHands[ACTIVE_DUELIST][i]->id == MONTAGE_DRAGON) {
        montageZone = (s8)i;
        break;
      }
    }
  }

  if (montageZone < 0)
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)montageZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}
