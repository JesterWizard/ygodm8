#ifndef GUARD_DIFFUSION_WAVE_MOTION_H
#define GUARD_DIFFUSION_WAVE_MOTION_H

#define DUEL_CURSOR_DIFFUSION_WAVE_MOTION_TARGET 33

u8 IsDiffusionWaveMotionCard(u16 cardId);
u8 FieldHasDiffusionWaveMotionTarget(u8 originFixedRow, u8 originFixedCol);
void BeginDiffusionWaveMotionTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectDiffusionWaveMotionTarget(void);
void CancelDiffusionWaveMotionTargeting(void);
void EffectDiffusionWaveMotion(void);

#endif // GUARD_DIFFUSION_WAVE_MOTION_H
