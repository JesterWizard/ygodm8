#ifndef GUARD_BIG_BANG_SHOT_H
#define GUARD_BIG_BANG_SHOT_H

#include "global.h"
#include "dynamic_equip.h"

#define BIG_BANG_SHOT_ATK_BONUS 400
#define BIG_BANG_SHOT_SLOTS_PER_DUELIST 3
#define BIG_BANG_SHOT_RAM_BYTES 6

extern u8 gBigBangShotTargetCol[BIG_BANG_SHOT_RAM_BYTES];

void EffectBigBangShot(void);
void BigBangShot_OnTargetZoneLeaving(struct DuelCard *zone);
u8 BigBangShot_ClaimEquipSlot(struct DuelCard *targetZone, struct DuelCard *spellZone);
void BigBangShot_ClearEquipBonus(const struct DynamicEquipLink *link);
void BigBangShot_ResetAllBoosts(void);
void ApplyBigBangShotAtkBonusToCardInfo(const struct DuelCard *zone);
void ApplyBigBangShotPiercingBattleEffect(void);

#endif // GUARD_BIG_BANG_SHOT_H
