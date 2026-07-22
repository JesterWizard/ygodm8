#ifndef GUARD_MORPHTRONIC_MAGNEN_BAR_H
#define GUARD_MORPHTRONIC_MAGNEN_BAR_H

#include "global.h"

#define MORPHTRONIC_MAGNEN_BAR_NO_ATTACK_MARK 0x40

u8 MorphtronicMagnenBar_CanDeclareAttack(const struct DuelCard *zone);
void MorphtronicMagnenBar_ClearAttackMarksAtEndPhase(void);

#endif /* GUARD_MORPHTRONIC_MAGNEN_BAR_H */
