#include "global.h"
#include "common-chax.h"
#include "amazoness_baby_tiger.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

#define BABY_TIGER_ATK_PER_AMAZONESS_GY 100

u8 GetDuelistForZone(struct DuelCard *zone);

static u8 CountAmazonessInGy(u8 fixedDuelist)
{
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (Duel_IsAmazonessCard(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 1;
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (Duel_IsAmazonessCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }
  return count;
}

u8 AmazonessBabyTiger_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 fixed;
  u16 atk;

  if (zone == NULL || zone->id != AMAZONESS_BABY_TIGER)
    return FALSE;

  fixed = GetDuelistForZone(zone);
  if (fixed > DUEL_OPPONENT)
    return FALSE;

  SetCardInfo(zone->id);
  atk = Duel_StatFromCount(CountAmazonessInGy(fixed), BABY_TIGER_ATK_PER_AMAZONESS_GY,
                           gCardInfo.atk);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

unsigned char CanActivateAMAZONESS_BABY_TIGER(void)
{
  if (gMonEffect.id != AMAZONESS_BABY_TIGER)
    return FALSE;

  /* Continuous GY ATK via AmazonessBabyTiger_ApplyDynamicZoneStats.
   * ponytail: Amazoness-Tiger name + on Amazoness summon SS need continuous/summon hooks.
   * Ceiling: SS from hand only. */
  return FALSE;
}

void ActivateAMAZONESS_BABY_TIGEREffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_BABY_TIGER, 2);
}

u8 CanSpecialSummonAmazonessBabyTigerFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;
  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != AMAZONESS_BABY_TIGER)
    return FALSE;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;
  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonAmazonessBabyTigerFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonAmazonessBabyTigerFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(AMAZONESS_BABY_TIGER, 2);
  if (IsDuelOver() == TRUE)
    return TRUE;
  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;
  UpdateDuelGfxExceptField();
  return TRUE;
}
