#ifndef GUARD_SUMMON_TRIBUTE_H
#define GUARD_SUMMON_TRIBUTE_H

extern u8 gPendingSummonTributeCount;
extern u16 gPendingTributeSummonCardId;
extern u8 gDoubleCostonDarkBonusPaid;

void RecordPendingSummonTributeCount(void);
void SetPendingSummonTributeCount(u8 tributeCount);
void ClearPendingSummonTributeCount(void);
u8 GetPendingSummonTributeCount(void);
void SetPendingTributeSummonCardId(u16 cardId);
void ClearPendingTributeSummonCardId(void);
u16 GetPendingTributeSummonCardId(void);
u8 PendingTributeSummonStillUnpaid(void);
u16 ResolveTributeSummonTarget(void);
void ClearDoubleCostonDarkBonusPaid(void);
void RecordDoubleCostonDarkBonusPaid(u8 bonusPaid);
u8 GetDoubleCostonDarkBonusPaid(void);

#endif // GUARD_SUMMON_TRIBUTE_H
