#ifndef GUARD_DOUBLE_TOOL_C_AND_D_H
#define GUARD_DOUBLE_TOOL_C_AND_D_H

#include "gba/types.h"

struct DuelCard;

#define DOUBLE_TOOL_C_AND_D_ATK_BOOST 1000

void ApplyDoubleToolCAndDAtkBonusToCardInfo(const struct DuelCard *zone);
u8 DoubleTool_ShouldNegateAttackTargetEffects(const struct DuelCard *attacker,
                                              const struct DuelCard *target);
struct DuelCard *DoubleTool_GetAttackRedirectTarget(const struct DuelCard *attacker);
u8 DoubleTool_ShouldDestroyBattleOpponent(const struct DuelCard *attacker,
                                          const struct DuelCard *defender);
void ApplyDoubleToolCAndDBattleEffect(void);

#endif /* GUARD_DOUBLE_TOOL_C_AND_D_H */
