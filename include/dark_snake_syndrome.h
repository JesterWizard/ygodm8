#ifndef GUARD_DARK_SNAKE_SYNDROME_H
#define GUARD_DARK_SNAKE_SYNDROME_H

#include "global.h"

u8 IsActivatedDarkSnakeSyndromeZone(const struct DuelCard *zone);
void TryApplyDarkSnakeSyndromeStandbyDamage(void);
void EffectDarkSnakeSyndrome(void);

#endif // GUARD_DARK_SNAKE_SYNDROME_H
