#ifndef GUARD_TRIBUTE_H
#define GUARD_TRIBUTE_H

void ResetNumTributes (void);
void IncrementNumTributes (void);
int GetMonsterNumRequiredTributes (unsigned short);
int GetMonsterNumRequiredTributesForHandSlot(u8 handSlot, u16 cardId);
unsigned char GetRitualNumRequiredTributes (unsigned short);
int GetNumRequiredTributes (unsigned short);

#endif // GUARD_TRIBUTE_H
