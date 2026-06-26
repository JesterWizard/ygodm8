#ifndef GUARD_AMAZONESS_ARCHER_H
#define GUARD_AMAZONESS_ARCHER_H

#define DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE1 27
#define DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE2 28
#define AMAZONESS_ARCHER_DAMAGE 1200

unsigned char CanActivateAmazonessArcher(void);
void ActivateAmazonessArcherEffect(void);
void BeginAmazonessArcherTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectAmazonessArcherTarget(void);

#endif // GUARD_AMAZONESS_ARCHER_H
