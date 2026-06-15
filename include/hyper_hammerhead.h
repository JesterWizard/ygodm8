#ifndef GUARD_HYPER_HAMMERHEAD_H
#define GUARD_HYPER_HAMMERHEAD_H

#define HYPER_HAMMERHEAD_PENDING_NONE 0xFF

extern u8 gPendingHyperHammerheadRow;
extern u8 gPendingHyperHammerheadCol;

void ApplyHyperHammerheadBattleEffect(void);
void ResolveHyperHammerheadBattleEffect(void);
void ClearHyperHammerheadPending(void);

#endif // GUARD_HYPER_HAMMERHEAD_H
