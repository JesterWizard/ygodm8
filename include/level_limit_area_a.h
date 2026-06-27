#ifndef GUARD_LEVEL_LIMIT_AREA_A_H
#define GUARD_LEVEL_LIMIT_AREA_A_H

#define LEVEL_LIMIT_AREA_A_MAX_FORCED_LEVEL 3

u8 IsActivatedLevelLimitAreaAZone(const struct DuelCard *zone);
u8 IsLevelLimitAreaAActiveOnField(void);
u8 LevelLimitAreaA_CannotUseDefensePosition(u16 cardId);
void LevelLimitAreaA_ForceOnZone(struct DuelCard *zone);
void LevelLimitAreaA_ForceOnSummon(struct DuelCard *zone);
void LevelLimitAreaA_ForceOnField(void);
void LevelLimitAreaA_CheckAfterFieldChange(void);
void TryLevelLimitAreaAOnMonsterPlacement(struct DuelCard *zone);
void TryActivateLevelLimitAreaAOnOpponentTurnStart(void);
void EffectLevelLimitAreaA(void);

#endif // GUARD_LEVEL_LIMIT_AREA_A_H
