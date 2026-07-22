#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "evil_hero_infernal_sniper.h"

#define INFERNAL_SNIPER_STANDBY_DAMAGE 1000

u8 EvilHeroInfernalSniper_PreventsDestroy(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != EVIL_HERO_INFERNAL_SNIPER || !zone->isFaceUp)
    return FALSE;

  if (gSpellEffectData.id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(gSpellEffectData.id) == TYPE_GROUP_SPELL;
}

unsigned char ShouldActivateEvilHeroInfernalSniperTurnEffect(void)
{
  return Duel_ShouldActivateTurnEffect(EVIL_HERO_INFERNAL_SNIPER, TRUE, FALSE);
}

void ActivateEvilHeroInfernalSniperTurnEffect(void)
{
  Duel_ChangeLpWithPrefaceText(INACTIVE_DUELIST, -(s32)INFERNAL_SNIPER_STANDBY_DAMAGE,
                               EVIL_HERO_INFERNAL_SNIPER, 9, TRUE);
}

unsigned char ShouldActivateEVIL_HERO_INFERNAL_SNIPER(void)
{
  /* Spell destroy immunity via EvilHeroInfernalSniper_PreventsDestroy;
   * Standby burn via ActivateEvilHeroInfernalSniperTurnEffect. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_INFERNAL_SNIPER(void)
{
}
