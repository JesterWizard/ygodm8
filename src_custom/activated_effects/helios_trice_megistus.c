#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "helios_trice_megistus.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

#define HELIOS_TRICE_STAT_PER_BANISHED 300

static u8 CountBanishedMonsters(void)
{
  u8 total = 0;
  u8 d;
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return 0;

  for (d = 0; d < 2; d++) {
    for (i = 0; i < RemovedFromPlay_GetCount(d); i++) {
      if (GetTypeGroup(RemovedFromPlay_GetCardAt(d, i)) == TYPE_GROUP_MONSTER)
        total++;
    }
  }
  return total;
}

u8 HeliosTriceMegistus_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 stat;

  if (zone == NULL || zone->id != HELIOS_TRICE_MEGISTUS)
    return FALSE;

  stat = Duel_StatFromCount(CountBanishedMonsters(), HELIOS_TRICE_STAT_PER_BANISHED, 0);
  Duel_WriteCardInfoStats(zone->id, stat, stat);
  return TRUE;
}

static struct DuelCard *FindHeliosDuoMegistusYouControl(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == HELIOS_DUO_MEGISTUS)
      return zone;
  }
  return NULL;
}

unsigned char CanActivateHELIOS_TRICE_MEGISTUS(void)
{
  if (gMonEffect.id != HELIOS_TRICE_MEGISTUS)
    return FALSE;

  /* Continuous ATK/DEF via HeliosTriceMegistus_ApplyDynamicZoneStats.
   * ponytail: extra battle + battle-destroy End Phase SS +500 need battle/EP hooks. */
  return FALSE;
}

void ActivateHELIOS_TRICE_MEGISTUSEffect(void)
{
  Duel_ShowEffectTextTyped(HELIOS_TRICE_MEGISTUS, 2);
}

u8 CanSpecialSummonHeliosTriceMegistusFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;
  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HELIOS_TRICE_MEGISTUS)
    return FALSE;
  if (FindHeliosDuoMegistusYouControl() == NULL)
    return FALSE;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;
  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonHeliosTriceMegistusFromHand(u8 handZone)
{
  struct DuelCard *tribute = FindHeliosDuoMegistusYouControl();
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonHeliosTriceMegistusFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(HELIOS_TRICE_MEGISTUS, 2);
  if (IsDuelOver() == TRUE)
    return TRUE;
  if (tribute != NULL)
    ClearZone(tribute);
  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  return TRUE;
}
