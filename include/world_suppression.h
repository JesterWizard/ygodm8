#ifndef GUARD_WORLD_SUPPRESSION_H
#define GUARD_WORLD_SUPPRESSION_H

#include "global.h"

#define TRAP_WORLD_SUPPRESSION 33

extern u8 gWorldSuppressionNegatesFieldSpells;

u8 WorldSuppression_IsFieldSpellCard(u16 cardId);
u8 IsWorldSuppressionNegatingFieldSpells(void);
u8 IsWorldSuppressionNegatingFieldSpell(u16 cardId);
void WorldSuppression_SetNegatingFieldSpells(void);
void WorldSuppression_ClearNegation(void);
u8 WorldSuppression_ShouldActivateTrapOnFieldSpell(u16 originCardId);
void EffectWorldSuppression(void);

#endif // GUARD_WORLD_SUPPRESSION_H
