#ifndef GUARD_LEVEL_LIMIT_AREA_B_H
#define GUARD_LEVEL_LIMIT_AREA_B_H

#define LEVEL_LIMIT_AREA_B_MIN_RESTRICTED_LEVEL 4

u8 IsActivatedLevelLimitAreaBZone(const struct DuelCard *zone);
u8 IsLevelLimitAreaBActiveOnField(void);
u8 LevelLimitAreaB_CannotUseAttackPosition(u16 cardId);
u8 LevelLimitAreaB_CanMonsterAttack(const struct DuelCard *zone);
void LevelLimitAreaB_EnforceOnZone(struct DuelCard *zone);
void LevelLimitAreaB_EnforceOnSummon(struct DuelCard *zone);
void LevelLimitAreaB_EnforceOnField(void);
void LevelLimitAreaB_CheckAfterFieldChange(void);
void TryLevelLimitAreaBOnMonsterPlacement(struct DuelCard *zone);
void EffectLevelLimitAreaB(void);

#endif // GUARD_LEVEL_LIMIT_AREA_B_H
