#ifndef GUARD_JOWLS_OF_DARK_DEMISE_H
#define GUARD_JOWLS_OF_DARK_DEMISE_H

#define DUEL_CURSOR_JOWLS_OF_DARK_DEMISE_TARGET 17

u8 CanJowlsControlledMonsterAttackDirectly(const struct DuelCard *zone);
unsigned char CanActivateJowlsOfDarkDemise(void);
void ActivateJowlsOfDarkDemiseEffect(void);
void TrySelectJowlsOfDarkDemiseTarget(void);
void CancelJowlsOfDarkDemiseTargeting(void);

#endif // GUARD_JOWLS_OF_DARK_DEMISE_H
