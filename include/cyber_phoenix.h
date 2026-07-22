#ifndef GUARD_CYBER_PHOENIX_H
#define GUARD_CYBER_PHOENIX_H

struct DuelCard;

unsigned char CanActivateCYBER_PHOENIX(void);
void ActivateCYBER_PHOENIXEffect(void);
u8 CyberPhoenix_BlocksSpellTrapTarget(const struct DuelCard *zone);

#endif /* GUARD_CYBER_PHOENIX_H */
