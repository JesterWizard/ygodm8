#ifndef GUARD_EVIL_HERO_DARKEST_KNIGHT_H
#define GUARD_EVIL_HERO_DARKEST_KNIGHT_H

#include "global.h"

struct DuelCard;

void EvilHeroDarkestKnight_OnFusionSummoned(struct DuelCard *zone, const u16 *materialIds,
                                            u8 materialCount);
void ApplyEvilHeroDarkestKnightOppAtkPenalty(struct DuelCard *zone);
void EvilHeroDarkestKnight_EnsureInit(void);

#endif /* GUARD_EVIL_HERO_DARKEST_KNIGHT_H */
