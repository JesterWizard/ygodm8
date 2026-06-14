#ifndef GUARD_TRIBUTE_H
#define GUARD_TRIBUTE_H

void ResetNumTributes (void);
void IncrementNumTributes (void);
void AddTributeCredit(u16 tributeCardId);
u8 CardQualifiesForDoubleCostonDarkBonus(u16 cardId);
u8 DoubleCostonCoversDarkTributeSummon(u16 summonCardId, u16 tributeCardId);
int GetMonsterNumRequiredTributes (unsigned short);
int GetMonsterNumRequiredTributesForHandSlot(u8 handSlot, u16 cardId);
unsigned char GetRitualNumRequiredTributes (unsigned short);
int GetNumRequiredTributes (unsigned short);

#endif // GUARD_TRIBUTE_H
