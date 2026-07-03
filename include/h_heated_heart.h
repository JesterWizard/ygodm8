#ifndef GUARD_H_HEATED_HEART_H
#define GUARD_H_HEATED_HEART_H

#include "gba/types.h"

#define DUEL_CURSOR_H_HEATED_HEART_TARGET 39
#define HEATED_HEART_ATK_BOOST 500

u8 IsHHeatedHeartCard(u16 cardId);
u8 FieldHasHHeatedHeartTarget(u8 originFixedRow, u8 originFixedCol);
void BeginHHeatedHeartTargeting(u8 originFixedRow, u8 originFixedCol);
void TrySelectHHeatedHeartTarget(void);
void CancelHHeatedHeartTargeting(void);
void EffectHHeatedHeart(void);
u8 MonsterHasHeatedHeartPiercing(u8 fixedRow, u8 fixedCol);
void ApplyHeatedHeartAtkBonusToCardInfo(const struct DuelCard *zone);
void ApplyHHeatedHeartPiercingBattleEffect(void);

#endif // GUARD_H_HEATED_HEART_H
