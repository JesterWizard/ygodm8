#ifndef GUARD_MAN_THRO_TRO_H
#define GUARD_MAN_THRO_TRO_H

#define DUEL_CURSOR_MAN_THRO_TRO_TARGET 15
#define MAN_THRO_TRO_DAMAGE 800

unsigned char CanActivateManThroTro(void);
void ActivateManThroTroEffect(void);
void BeginManThroTroTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectManThroTroTarget(void);

#endif // GUARD_MAN_THRO_TRO_H
