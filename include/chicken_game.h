#ifndef GUARD_CHICKEN_GAME_H
#define GUARD_CHICKEN_GAME_H

#include "gba/types.h"

#define CHICKEN_GAME_LP_COST 1000
#define CHICKEN_GAME_LP_GAIN 1000
#define CHICKEN_GAME_DRAW_COUNT 1

struct DuelCard;

u8 ChickenGame_FaceUpOnField(void);
u8 ChickenGame_CanActivateIgnition(struct DuelCard *zone);
u8 ChickenGame_PlayerHasLowestLifePoints(u8 fixedDuelist);
u8 ChickenGame_ShouldBlockBattleDamage(u8 damagedFixedDuelist);
u8 ChickenGame_ShouldSkipTrapChain(void);
void ChickenGame_BeginIgnitionNoResponse(void);
void ChickenGame_EndIgnitionNoResponse(void);

#endif /* GUARD_CHICKEN_GAME_H */
