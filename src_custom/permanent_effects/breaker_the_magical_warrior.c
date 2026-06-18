#include "global.h"
#include "common-chax.h"
#include "breaker_the_magical_warrior.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"

extern unsigned char IsSkillDrainActiveOnField(void);
extern unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId);
extern void UpdateDuelGfxExceptField(void);
void FlipCardFaceUp(struct DuelCard *zone);

static u8 IsBreakerNormalSummonPlacement(const struct DuelCard *zone)
{
  /* ponytail: hand normal summon copies isFaceUp=0; attack-position monsters still count */
  return zone->isFaceUp || !zone->isDefending;
}

u8 BreakerTheMagicalWarrior_ZoneHasSpellCounter(const struct DuelCard *zone)
{
  return zone != NULL
      && zone->id == BREAKER_THE_MAGICAL_WARRIOR
      && zone->permStage > 0;
}

void BreakerTheMagicalWarrior_ClearZoneSpellCounter(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != BREAKER_THE_MAGICAL_WARRIOR)
    return;

  if (zone->permStage > 0)
    DecrementPermStage(zone);
}

void TryBreakerTheMagicalWarriorOnMonsterPlacement(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != BREAKER_THE_MAGICAL_WARRIOR)
    return;

  /* ponytail: placement hook is hand normal/tribute summon only — special summons use duel_helpers */
  if (!IsBreakerNormalSummonPlacement(zone) || BreakerTheMagicalWarrior_ZoneHasSpellCounter(zone))
    return;

  if (IsSkillDrainActiveOnField()
      && TryActivateSkillDrainAndNegateCardId(BREAKER_THE_MAGICAL_WARRIOR))
    return;

  if (!zone->isFaceUp)
    FlipCardFaceUp(zone);

  IncrementPermStage(zone);
  Duel_NotifyMonsterZoneChanged(zone);
  Duel_RefreshMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

void BreakerTheMagicalWarrior_SelfCheck(void)
{
  struct DuelCard *zone = gFixedZones[PLAYER_MONSTER_ROW][0];

  zone->id = BREAKER_THE_MAGICAL_WARRIOR;
  zone->permStage = 0;
  IncrementPermStage(zone);
  if (zone->permStage != 1)
    while (1)
      ;
  DecrementPermStage(zone);
  if (zone->permStage != 0)
    while (1)
      ;
  zone->id = CARD_NONE;
}
