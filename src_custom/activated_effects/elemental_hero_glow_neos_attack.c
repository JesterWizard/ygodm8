#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_glow_neos.h"

u8 ElementalHeroGlowNeos_CanDeclareAttack(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_GLOW_NEOS)
    return TRUE;

  return (zone->unk4 & ELEMENTAL_HERO_GLOW_NEOS_CANNOT_ATTACK_MARK) == 0;
}

u8 ElementalHeroGlowNeos_CanAttackDirectly(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_GLOW_NEOS)
    return FALSE;

  return (zone->unk4 & ELEMENTAL_HERO_GLOW_NEOS_DIRECT_ATTACK_MARK) != 0;
}

void ElementalHeroGlowNeos_ClearTurnMarksAtEndPhase(void)
{
  u8 fixedRow;
  u8 col;
  u8 mask = (u8)(ELEMENTAL_HERO_GLOW_NEOS_CANNOT_ATTACK_MARK
      | ELEMENTAL_HERO_GLOW_NEOS_DIRECT_ATTACK_MARK);

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (zone != NULL && zone->id == ELEMENTAL_HERO_GLOW_NEOS)
        zone->unk4 &= (u8)~mask;
    }
  }
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroGlowNeos_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = ELEMENTAL_HERO_GLOW_NEOS;
  zone.unk4 = ELEMENTAL_HERO_GLOW_NEOS_CANNOT_ATTACK_MARK;
  if (ElementalHeroGlowNeos_CanDeclareAttack(&zone) != FALSE)
    __builtin_trap();

  zone.unk4 = ELEMENTAL_HERO_GLOW_NEOS_DIRECT_ATTACK_MARK;
  if (ElementalHeroGlowNeos_CanAttackDirectly(&zone) == FALSE)
    __builtin_trap();
}
#endif
