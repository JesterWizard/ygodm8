#ifndef GUARD_CARD_PASSIVES_H
#define GUARD_CARD_PASSIVES_H

#include "global.h"

u8 IsImmuneToControlSwitch(u16 cardId);
extern u16 gChaosCommandMagicianBlockedOriginMonsterEffectId;

u8 TryNegateChaosCommandMagicianTargetedMonsterEffect(u16 originCardId, u8 targetFixedRow,
                                                     u8 targetFixedCol);
u8 Duel_TryNegateMonsterEffectOnTarget(u16 originCardId, u8 targetFixedRow, u8 targetFixedCol);
u8 Duel_TryNegateMonsterEffectOnZone(u16 originCardId, struct DuelCard *zone);
u8 Duel_TryNegateMonsterEffectTargetSelection(void);
u8 Duel_MonsterEffectConfirmTargetForAi(u16 originCardId, u8 targetRow, u8 targetCol);
u8 Duel_ShouldSuppressChaosCommandMagicianBlockedMonsterEffectText(u16 cardId);
u8 IsImmuneToHarmfulTargetedEffectsOnField(u16 cardId, u8 turnRow);
u8 IsImmuneToSpellEffectsOnField(u16 cardId, u8 turnRow);
u8 IsImmuneToTrapEffectsOnField(u16 cardId, u8 turnRow);
u8 HasDoublePiercingBattleDamage(u16 cardId);
void ApplyBlueEyesChaosMaxDragonDoublePiercingDamage(void);

#endif // GUARD_CARD_PASSIVES_H
