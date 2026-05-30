#ifndef GUARD_MYSTICAL_SPACE_TYPHOON_H
#define GUARD_MYSTICAL_SPACE_TYPHOON_H

#define DUEL_CURSOR_MST_TARGET 3

u8 IsMysticalSpaceTyphoonCard(u16 cardId);
u8 FieldHasMysticalSpaceTyphoonTarget(u8 originFixedRow, u8 originFixedCol);
void BeginMysticalSpaceTyphoonTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectMysticalSpaceTyphoonTarget(void);
void CancelMysticalSpaceTyphoonTargeting(void);
void EffectMysticalSpaceTyphoon(void);

#endif // GUARD_MYSTICAL_SPACE_TYPHOON_H
