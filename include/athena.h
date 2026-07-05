#ifndef GUARD_ATHENA_H
#define GUARD_ATHENA_H

#define DUEL_CURSOR_ATHENA_COST_TARGET 41

void TryAthenaOnMonsterPlacement(struct DuelCard *zone);

unsigned char CanActivateATHENA(void);
void ActivateATHENAEffect(void);
void TrySelectAthenaCostTarget(void);
void CancelAthenaCostTargeting(void);

#endif // GUARD_ATHENA_H
