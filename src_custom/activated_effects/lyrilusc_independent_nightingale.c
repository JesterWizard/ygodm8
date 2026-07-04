#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "lyrilusc_independent_nightingale.h"
#include "monster_effect_usage.h"

#define NIGHTINGALE_BASE_ATK 1000
#define NIGHTINGALE_STAT_PER_LEVEL 500

static u8 NightingaleLevel(u16 cardId)
{
  /* ponytail: no per-zone level yet — Xyz-material Level boost needs zone level storage. */
  SetCardInfo(cardId);
  return gCardInfo.level;
}

static u16 NightingaleCurrentAtk(u16 cardId)
{
  return Duel_StatFromCount(NightingaleLevel(cardId), NIGHTINGALE_STAT_PER_LEVEL, NIGHTINGALE_BASE_ATK);
}

static s32 NightingaleBurnDamage(u16 cardId)
{
  return (s32)NightingaleLevel(cardId) * NIGHTINGALE_STAT_PER_LEVEL;
}

u8 LyriluscIndependentNightingale_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 def;

  if (zone == NULL || zone->id != LYRILUSC_INDEPENDENT_NIGHTINGALE)
    return FALSE;

  SetCardInfo(zone->id);
  def = gCardInfo.def;
  Duel_WriteCardInfoStats(zone->id, NightingaleCurrentAtk(zone->id), def);
  return TRUE;
}

unsigned char CanActivateLyriluscIndependentNightingale(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (gMonEffect.id != LYRILUSC_INDEPENDENT_NIGHTINGALE)
    return FALSE;

  return NightingaleBurnDamage(zone->id) > 0;
}

void ActivateLyriluscIndependentNightingaleEffect(void)
{
  s32 damage = NightingaleBurnDamage(LYRILUSC_INDEPENDENT_NIGHTINGALE);

  if (damage <= 0)
    return;

  Duel_ChangeLpWithPrefaceText(INACTIVE_DUELIST, -damage, LYRILUSC_INDEPENDENT_NIGHTINGALE, 2, TRUE);
}

#if !defined(__GNUC__)
#error Lyrilusc Independent Nightingale self-check requires GCC
#elif __GNUC__
void LyriluscIndependentNightingale_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = LYRILUSC_INDEPENDENT_NIGHTINGALE;
  LyriluscIndependentNightingale_ApplyDynamicZoneStats(&zone);
}
#endif
