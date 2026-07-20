#ifndef GUARD_EFFECT_CONDITIONS_H
#define GUARD_EFFECT_CONDITIONS_H

#include "global.h"
#include "duel_helpers.h"

/* Condition registry (Phase 2). Reusable PickZone / gate predicates.
 * See documentation/effect-data-system.md.
 */

enum EffectCondId {
  EFFECT_COND_OPP_BACKROW_SPELL_TRAP = 0,
  EFFECT_COND_ACTIVE_FACE_UP_SPELL,
  EFFECT_COND_OPP_MONSTER,
  EFFECT_COND_ANY_FACE_UP_MONSTER,
  EFFECT_COND_COUNT
};

typedef u8 (*EffectCondFn)(u8 fixedRow, u8 fixedCol);

EffectCondFn EffectCond_Get(u8 condId);
u8 EffectCond_Eval(u8 condId, u8 fixedRow, u8 fixedCol);

/* Named helpers (same as registry entries; usable as PickZoneValidator). */
u8 EffectCond_OppBackrowSpellTrap(u8 fixedRow, u8 fixedCol);
u8 EffectCond_ActiveFaceUpSpell(u8 fixedRow, u8 fixedCol);
u8 EffectCond_OppMonster(u8 fixedRow, u8 fixedCol);
u8 EffectCond_AnyFaceUpMonster(u8 fixedRow, u8 fixedCol);

/* Parameterized: spell/trap on a specific fixed backrow (e.g. rival of controller). */
u8 EffectCond_SpellTrapOnBackrow(u8 requiredBackrow, u8 fixedRow, u8 fixedCol);

u8 EffectCond_ActiveBackrowFixedRow(void);
u8 EffectCond_InactiveMonsterFixedRow(void);

#endif /* GUARD_EFFECT_CONDITIONS_H */
