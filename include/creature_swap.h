#ifndef GUARD_CREATURE_SWAP_H
#define GUARD_CREATURE_SWAP_H

#define DUEL_CURSOR_CREATURE_SWAP_OWN 18

extern u8 gCreatureSwapPlayerRow;
extern u8 gCreatureSwapPlayerCol;
extern u8 gCreatureSwapOppRow;
extern u8 gCreatureSwapOppCol;

u8 IsCreatureSwapCard(u16 cardId);
u8 FieldHasCreatureSwapTarget(u8 originFixedRow, u8 originFixedCol);
void BeginCreatureSwapTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectCreatureSwapOwnTarget(void);
void CancelCreatureSwapTargeting(void);

#endif // GUARD_CREATURE_SWAP_H
