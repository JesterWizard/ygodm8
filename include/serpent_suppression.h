#ifndef GUARD_SERPENT_SUPPRESSION_H
#define GUARD_SERPENT_SUPPRESSION_H

#include "duel.h"

u8 SerpentSuppression_PreventsBattleDestruction(const struct DuelCard *defender,
                                                 const struct DuelCard *attacker);
void TryActivateSERPENT_SUPPRESSIONOnOpponentTurnStart(void);

#endif
