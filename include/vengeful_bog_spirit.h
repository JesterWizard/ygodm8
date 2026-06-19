#ifndef GUARD_VENGEFUL_BOG_SPIRIT_H
#define GUARD_VENGEFUL_BOG_SPIRIT_H

#include "global.h"

extern u8 gVengefulBogSpiritSummonedMaskOpponentRow;
extern u8 gVengefulBogSpiritSummonedMaskPlayerRow;

u8 IsActivatedVengefulBogSpiritZone(const struct DuelCard *zone);
u8 IsVengefulBogSpiritActiveOnField(void);
u8 VengefulBogSpirit_CanMonsterAttack(const struct DuelCard *zone);
void TryVengefulBogSpiritOnMonsterPlacement(struct DuelCard *zone);
void TryVengefulBogSpiritOnFlipSummon(struct DuelCard *zone);
void VengefulBogSpirit_ClearAllMarks(void);
void VengefulBogSpirit_ClearZoneMark(struct DuelCard *zone);
void VengefulBogSpirit_TransferZoneMark(struct DuelCard *dst, struct DuelCard *src);
void EffectVengefulBogSpirit(void);

#endif // GUARD_VENGEFUL_BOG_SPIRIT_H
