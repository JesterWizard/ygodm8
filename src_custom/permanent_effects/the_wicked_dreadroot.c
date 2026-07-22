#include "global.h"
#include "common-chax.h"
#include "card.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "the_wicked_dreadroot.h"
#include "mini_card.h"

void UpdateDuelGfxExceptField(void);

#define WICKED_DREADROOT_SUMMON_TEXT_SHOWN 1

static u8 IsActiveWickedDreadroot(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != THE_WICKED_DREADROOT)
    return FALSE;

  if (IsCardFaceUp((struct DuelCard *)zone))
    return TRUE;

  /* Attack-position summons stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 ZoneQualifiesForWickedDreadrootHalving(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || zone->id == THE_WICKED_DREADROOT)
    return FALSE;

  /* gCardData_NEW type check — avoids GetTypeGroup clobbering gCardInfo. */
  if (gCardInfo.id != zone->id || gCardInfo.type >= TYPE_SPELL)
    return FALSE;

  return ZoneShowsCombatStats(zone);
}

static struct DuelCard *FindActiveWickedDreadroot(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (IsActiveWickedDreadroot(zone))
        return zone;
    }
  }

  return NULL;
}

u8 TheWickedDreadroot_IsActiveOnField(void)
{
  return FindActiveWickedDreadroot() != NULL;
}

void ApplyTheWickedDreadrootStatHalving(const struct DuelCard *zone)
{
  if (!ZoneQualifiesForWickedDreadrootHalving(zone))
    return;

  if (FindActiveWickedDreadroot() == NULL)
    return;

  gCardInfo.atk = (u16)(gCardInfo.atk / 2);
  gCardInfo.def = (u16)(gCardInfo.def / 2);
}

void TheWickedDreadroot_RefreshStatsIfActive(void)
{
  if (TheWickedDreadroot_IsActiveOnField())
    RefreshFieldMonsterStatOverlays();
}

void TryTheWickedDreadrootOnMonsterPlacement(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  TheWickedDreadroot_RefreshStatsIfActive();
}

void TryTheWickedDreadrootEffectTextOnMonsterPlacement(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != THE_WICKED_DREADROOT)
    return;

  if (zone->unk4 != 0 || !IsActiveWickedDreadroot(zone))
    return;

  zone->unk4 = WICKED_DREADROOT_SUMMON_TEXT_SHOWN;
  UpdateDuelGfxExceptField();
  Duel_ShowEffectText(THE_WICKED_DREADROOT);
}

void TheWickedDreadroot_OnZoneCleared(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != THE_WICKED_DREADROOT)
    return;

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TheWickedDreadroot_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = THE_WICKED_DREADROOT;
  zone.isFaceUp = FALSE;
  zone.isDefending = FALSE;
  if (!IsActiveWickedDreadroot(&zone))
    __builtin_trap();
}
#endif
