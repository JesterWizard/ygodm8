#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "lyrilusc_independent_nightingale.h"
#include "monster_effect_usage.h"

#define NIGHTINGALE_BASE_ATK 1000
#define NIGHTINGALE_STAT_PER_LEVEL 500

u16 LyriluscIndependentNightingale_CopiedAtkBonus(struct DuelCard *hostZone)
{
  if (hostZone == NULL)
    return 0;

  SetCardInfo(Duel_EffectHostCardId(hostZone));
  return (u16)gCardInfo.level * NIGHTINGALE_STAT_PER_LEVEL;
}

static u16 NightingaleCurrentAtk(struct DuelCard *zone)
{
  return Duel_ClampStat((u32)NIGHTINGALE_BASE_ATK
                        + (u32)LyriluscIndependentNightingale_CopiedAtkBonus(zone));
}

static s32 NightingaleBurnDamage(struct DuelCard *zone)
{
  SetCardInfo(Duel_EffectHostCardId(zone));
  return (s32)gCardInfo.level * NIGHTINGALE_STAT_PER_LEVEL;
}

u8 LyriluscIndependentNightingale_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != LYRILUSC_INDEPENDENT_NIGHTINGALE)
    return FALSE;

  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, NightingaleCurrentAtk(zone), gCardInfo.def);
  return TRUE;
}

unsigned char CanActivateLyriluscIndependentNightingale(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!Duel_ZoneHasEffectOfCard(zone, LYRILUSC_INDEPENDENT_NIGHTINGALE))
    return FALSE;

  return NightingaleBurnDamage(zone) > 0;
}

void ActivateLyriluscIndependentNightingaleEffect(void)
{
  struct DuelCard *zone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  s32 damage = NightingaleBurnDamage(zone);

  if (damage <= 0)
    return;

  Duel_ChangeLpWithPrefaceText(INACTIVE_DUELIST, -damage, LYRILUSC_INDEPENDENT_NIGHTINGALE, 2,
                               TRUE);
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
