#ifndef GUARD_MIRROR_WALL_H
#define GUARD_MIRROR_WALL_H

#include "global.h"
#include "riryoku.h"

extern u8 gMirrorWallHalvedMask[MAX_DUEL_BOARD_CELLS];

u8 IsActivatedMirrorWallZone(const struct DuelCard *zone);
u8 IsMirrorWallActiveOnField(void);
void MarkMirrorWallJustSet(struct DuelCard *zone);
void AgeMirrorWallSetFlags(void);
unsigned char ShouldActivateMirrorWallUpkeep(void);
void ActivateMirrorWallUpkeep(void);
void TryApplyMirrorWallToPendingAction(void);
void ApplyMirrorWallAtkHalving(const struct DuelCard *zone);
void ClearMirrorWallHalvedZone(const struct DuelCard *zone);
void ClearMirrorWallHalvedMask(void);
void MirrorWall_OnZoneCleared(const struct DuelCard *zone);

#endif // GUARD_MIRROR_WALL_H
