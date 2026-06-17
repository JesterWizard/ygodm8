#ifndef GUARD_CARD_PASSIVES_H
#define GUARD_CARD_PASSIVES_H

#include "global.h"

u8 IsImmuneToControlSwitch(u16 cardId);
u8 IsImmuneToHarmfulTargetedEffectsOnField(u16 cardId, u8 turnRow);
u8 IsImmuneToSpellEffectsOnField(u16 cardId, u8 turnRow);
u8 IsImmuneToTrapEffectsOnField(u16 cardId, u8 turnRow);
u8 HasDoublePiercingBattleDamage(u16 cardId);
void ApplyBlueEyesChaosMaxDragonDoublePiercingDamage(void);

#endif // GUARD_CARD_PASSIVES_H
