#ifndef GUARD_NIGHTMARE_WHEEL_H
#define GUARD_NIGHTMARE_WHEEL_H

#define DUEL_CURSOR_NIGHTMARE_WHEEL_TARGET 22

u8 IsNightmareWheelCard(u16 cardId);
u8 CanActivateNightmareWheel(void);
u8 FieldHasNightmareWheelTarget(u8 originFixedRow, u8 originFixedCol);
void BeginNightmareWheelTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectNightmareWheelTarget(void);
void CancelNightmareWheelTargeting(void);
void EffectNightmareWheel(void);
u8 IsActivatedNightmareWheelZone(const struct DuelCard *zone);
u8 NightmareWheel_CanMonsterDeclareAttack(const struct DuelCard *zone);
u8 NightmareWheel_CannotChangeBattlePosition(const struct DuelCard *zone);
void TryApplyNightmareWheelOnTargetLeave(struct DuelCard *zone);
void TryApplyNightmareWheelStandbyDamage(void);

#endif // GUARD_NIGHTMARE_WHEEL_H
