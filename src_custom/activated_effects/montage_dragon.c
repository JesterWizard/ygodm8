#include "global.h"
#include "common-chax.h"
#include "montage_dragon.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "expanded_card_hand.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

#define MONTAGE_ATK_PER_LEVEL 300

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
    if (IsOtherHandMonster(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id))
      count++;
  }
  return count;
}

static u8 DiscardThreeMonstersSumLevels(void)
{
  u8 levels = 0;
  u8 discarded = 0;
  u8 i;

  for (i = 0; i < 3; i++) {
    s8 zone;
    struct DuelCard *slot;

    if (WhoseTurn() == DUEL_PLAYER)
      zone = SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], IsOtherHandMonster);
    else {
      u8 j;
      zone = -1;
      for (j = 0; j < MAX_ZONES_IN_ROW; j++) {
        if (IsOtherHandMonster(gTurnHands[ACTIVE_DUELIST][j]->id)) {
          zone = (s8)j;
          break;
        }
      }
    }

    if (zone < 0)
      break;

    slot = ExpandedHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)zone);
    SetCardInfo(slot->id);
    levels = (u8)(levels + gCardInfo.level);
    ClearZoneAndSendMonToGraveyard(slot, ACTIVE_DUELIST);
    discarded++;
    if (IsDuelOver() == TRUE)
      break;
  }
  return discarded == 3 ? levels : 0;
}

u8 MontageDragon_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id != MONTAGE_DRAGON)
    return FALSE;

  atk = Duel_StatFromCount(zone->unk4, MONTAGE_ATK_PER_LEVEL, 0);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

unsigned char CanActivateMONTAGE_DRAGON(void)
{
  if (gMonEffect.id != MONTAGE_DRAGON)
    return FALSE;

  /* ATK via MontageDragon_ApplyDynamicZoneStats (unk4 = sent Levels). */
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
  u8 levels;
  struct DuelCard *self;
  u8 col;

  if (!CanSpecialSummonMontageDragonFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(MONTAGE_DRAGON, 2);
  if (IsDuelOver() == TRUE)
    return TRUE;

  levels = DiscardThreeMonstersSumLevels();
  if (levels == 0 || IsDuelOver() == TRUE)
    return FALSE;

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

  self = NULL;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == MONTAGE_DRAGON) {
      self = zone;
      break;
    }
  }
  if (self != NULL)
    self->unk4 = levels;

  UpdateDuelGfxExceptField();
  return TRUE;
}
