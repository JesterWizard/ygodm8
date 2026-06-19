#ifndef GUARD_DUEL_ATTACK_RESTRICTIONS_H
#define GUARD_DUEL_ATTACK_RESTRICTIONS_H

#include "gba/types.h"
#include "duel.h"

enum DuelAttackRestrictionBit {
  DUEL_ATTACK_RESTRICT_SORL = 1 << 0,
  DUEL_ATTACK_RESTRICT_GRAVITY_BIND = 1 << 1,
  DUEL_ATTACK_RESTRICT_LEVEL_LIMIT_AREA_B = 1 << 2,
  DUEL_ATTACK_RESTRICT_VENGEFUL_BOG_SPIRIT = 1 << 3,
  DUEL_ATTACK_RESTRICT_WALL_OF_REVEALING_LIGHT = 1 << 4,
};

extern u8 gDuelAttackRestrictionsActive;

void Duel_ResetAttackRestrictions(void);
void Duel_RefreshAttackRestrictions(void);
u8 Duel_CanMonsterDeclareAttack(const struct DuelCard *zone);

#endif // GUARD_DUEL_ATTACK_RESTRICTIONS_H
