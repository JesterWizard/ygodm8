#ifndef GUARD_DARK_DUST_SPIRIT_H
#define GUARD_DARK_DUST_SPIRIT_H

void TryActivateDarkDustSpiritOnMonsterPlacement(struct DuelCard *zone);
unsigned char CanActivateDarkDustSpirit(void);
void ActivateDarkDustSpiritEffect(void);
unsigned char ShouldActivateDarkDustSpiritSummon(void);
void ActivateDarkDustSpiritSummon(void);
unsigned char ShouldActivateDarkDustSpiritTurnEffect(void);
void ActivateDarkDustSpiritTurnEffect(void);

#endif // GUARD_DARK_DUST_SPIRIT_H
