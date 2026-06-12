#ifndef GUARD_SUMMON_TRIBUTE_H
#define GUARD_SUMMON_TRIBUTE_H

extern u8 gPendingSummonTributeCount;

void RecordPendingSummonTributeCount(void);
void SetPendingSummonTributeCount(u8 tributeCount);
void ClearPendingSummonTributeCount(void);
u8 GetPendingSummonTributeCount(void);

#endif // GUARD_SUMMON_TRIBUTE_H
