#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

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

static struct DuelCard *FindHeliosThePrimordialSunYouControl(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == HELIOS_THE_PRIMORDIAL_SUN)
      return zone;
  }

  return NULL;
}

unsigned char CanActivateHELIOS_DUO_MEGISTUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HELIOS_DUO_MEGISTUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HELIOS_DUO_MEGISTUS)
    return FALSE;

  /* ponytail: battle-destroy End Phase SS Megistus needs battle/EP hooks.
   * Ceiling: OPT refresh stages from banished-monster count. */
  return CanUseMonsterEffect(zone);
}

void ActivateHELIOS_DUO_MEGISTUSEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 banished;
  u8 stages;

  Duel_ShowEffectTextTyped(HELIOS_DUO_MEGISTUS, 2);

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  banished = CountBanishedMonsters();
  stages = (u8)((banished * 200) / 500);
  if (stages > 20)
    stages = 20;

  SetPermStage(zone, stages);
  MarkMonsterEffectUsed(zone);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

u8 CanSpecialSummonHeliosDuoMegistusFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HELIOS_DUO_MEGISTUS)
    return FALSE;

  if (FindHeliosThePrimordialSunYouControl() == NULL)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonHeliosDuoMegistusFromHand(u8 handZone)
{
  struct DuelCard *tribute = FindHeliosThePrimordialSunYouControl();
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *self;
  u8 banished;
  u8 stages;

  if (!CanSpecialSummonHeliosDuoMegistusFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(HELIOS_DUO_MEGISTUS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (tribute != NULL)
    ClearZone(tribute);

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  self = NULL;
  {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

      if (zone != NULL && zone->id == HELIOS_DUO_MEGISTUS) {
        self = zone;
        break;
      }
    }
  }

  banished = CountBanishedMonsters();
  stages = (u8)((banished * 200) / 500);
  if (stages > 20)
    stages = 20;

  if (self != NULL) {
    /* ponytail: permStage unit is ~500 ATK/DEF each, not exact banished×200 overlay. */
    SetPermStage(self, stages);
  }

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonHeliosDuoMegistusFromHand(u8 handZone);
u8 TrySpecialSummonHeliosDuoMegistusFromHand(u8 handZone);
#endif
