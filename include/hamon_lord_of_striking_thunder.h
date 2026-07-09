#ifndef GUARD_HAMON_LORD_OF_STRIKING_THUNDER_H
#define GUARD_HAMON_LORD_OF_STRIKING_THUNDER_H

#include "global.h"

#define HAMON_BATTLE_BURN_DAMAGE 1000
#define HAMON_CONTINUOUS_SPELL_COST 3
#define HAMON_BATTLE_PENDING_NONE 0xFF

extern u8 gPendingHamonBattleBurnDuelist;
extern u16 gPendingHamonBattleBurnEffectCardId;

u8 CanSpecialSummonHamonLordOfStrikingThunderFromHand(u8 handZone);
u8 TrySpecialSummonHamonLordOfStrikingThunderFromHand(u8 handZone);
struct DuelCard *HamonLordOfStrikingThunder_GetForcedAttackTarget(u8 defenderDuelist);
u8 HamonLordOfStrikingThunder_CanAttackMonsterZone(struct DuelCard *zone);
void ApplyHamonLordOfStrikingThunderBattleEffect(void);
void ResolveHamonLordOfStrikingThunderBattleEffect(void);

#endif
