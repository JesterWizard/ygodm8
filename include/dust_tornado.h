#ifndef GUARD_DUST_TORNADO_H
#define GUARD_DUST_TORNADO_H

#define DUEL_CURSOR_DUST_TORNADO_TARGET 23

u8 IsDustTornadoCard(u16 cardId);
u8 FieldHasDustTornadoTarget(u8 originFixedRow, u8 originFixedCol);
void BeginDustTornadoTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectDustTornadoTarget(void);
void CancelDustTornadoTargeting(void);
void EffectDustTornado(void);

#endif // GUARD_DUST_TORNADO_H
