#ifndef GUARD_LIGHT_END_DRAGON_H
#define GUARD_LIGHT_END_DRAGON_H

#define DUEL_CURSOR_LIGHT_END_DRAGON_TARGET 47

extern s8 gLightEndDragonDefStages[6];

void TrySelectLightEndDragonTarget(void);
void CancelLightEndDragonTargeting(void);
void ClearLightEndDragonDefStages(void);
void ApplyLightEndDragonDefStagesToCardInfo(const struct DuelCard *zone);

#endif // GUARD_LIGHT_END_DRAGON_H
