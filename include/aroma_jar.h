#ifndef GUARD_AROMA_JAR_H
#define GUARD_AROMA_JAR_H

#include "global.h"

#define AROMA_JAR_FLIPPED 1

u8 AromaJar_PreventsBattleDestroy(const struct DuelCard *zone);
void TryAromaJarOnFaceUp(struct DuelCard *zone);
void TryApplyAromaJarEndPhase(void);

#endif /* GUARD_AROMA_JAR_H */
