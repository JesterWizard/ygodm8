#ifndef GUARD_LINKED_REVIVE_TRAP_H
#define GUARD_LINKED_REVIVE_TRAP_H

#include "effect.h"

/* Continuous revive traps that destroy each other with the summoned monster.
 * trapZone->unk4 = monster turn-col + 1 while linked. */
void LinkedReviveTrap_Link(struct DuelCard *trapZone, u8 monsterTurnCol);

u8 Cond_LinkedReviveTrapOnLeave(struct EffectCtx *ctx);
enum DuelActionResult Op_LinkedReviveTrapOnLeave(struct EffectCtx *ctx);

#endif /* GUARD_LINKED_REVIVE_TRAP_H */
