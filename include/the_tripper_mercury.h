#ifndef GUARD_THE_TRIPPER_MERCURY_H
#define GUARD_THE_TRIPPER_MERCURY_H

void FinishTheTripperMercuryTributeSummon(struct DuelCard *zone, u8 fixedRow, u8 fixedCol);
unsigned char ShouldActivateTheTripperMercury(void);
void ActivateTheTripperMercury(void);
u8 TheTripperMercury_DrainActiveOnTurnRow(u8 turnRow);
void ApplyTheTripperMercuryOpponentAtkDrain(struct DuelCard *zone);
void TryUnlockTheTripperMercuryForSecondAttack(struct DuelCard *attacker);

#endif // GUARD_THE_TRIPPER_MERCURY_H
