#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_lady_heat.h"
#include "monster_effect_usage.h"

#define LADY_HEAT_DAMAGE_PER_ELEMENTAL_HERO 200

static const char sElementalHeroArchetypeName[] APPEND_RODATA = "Elemental HERO";

static u8 IsElementalHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sElementalHeroArchetypeName);
}

static u8 CountFaceUpElementalHeroOnMonsterRow(u8 turnMonsterRow)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnMonsterRow][col];

    if (zone->id == CARD_NONE || !zone->isFaceUp)
      continue;

    if (IsElementalHeroMonster(zone->id))
      count++;
  }

  return count;
}

static u8 CountElementalHeroForLadyHeatCanActivate(struct DuelCard *activator)
{
  u8 count = CountFaceUpElementalHeroOnMonsterRow(ACTIVE_DUELIST_MONSTER_ROW);

  // ponytail: CanActivate runs before the menu flips a face-down activator
  if (activator != NULL && !activator->isFaceUp && IsElementalHeroMonster(activator->id))
    count++;

  return count;
}

unsigned char CanActivateElementalHeroLadyHeat(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (gMonEffect.id != ELEMENTAL_HERO_LADY_HEAT)
    return FALSE;

  return CountElementalHeroForLadyHeatCanActivate(zone) > 0;
}

void ActivateElementalHeroLadyHeatEffect(void)
{
  u8 count = CountFaceUpElementalHeroOnMonsterRow(ACTIVE_DUELIST_MONSTER_ROW);
  s32 damage = (s32)count * LADY_HEAT_DAMAGE_PER_ELEMENTAL_HERO;

  if (damage <= 0)
    return;

  Duel_ChangeLpWithPrefaceText(INACTIVE_DUELIST, -damage, ELEMENTAL_HERO_LADY_HEAT, 2, TRUE);
}

#if !defined(__GNUC__)
unsigned char CanActivateElementalHeroLadyHeat(void);
void ActivateElementalHeroLadyHeatEffect(void);
#endif
