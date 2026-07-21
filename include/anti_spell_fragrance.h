#ifndef GUARD_ANTI_SPELL_FRAGRANCE_H
#define GUARD_ANTI_SPELL_FRAGRANCE_H

#include "gba/types.h"

/* TRUE → forbid activating this Spell from a face-up / hand play (must Set first). */
u8 AntiSpellFragrance_BlocksSpellActivation(struct DuelCard *spellZone);
void TryActivateANTI_SPELL_FRAGRANCEOnOpponentTurnStart(void);

#endif /* GUARD_ANTI_SPELL_FRAGRANCE_H */
