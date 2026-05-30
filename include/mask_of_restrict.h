#ifndef GUARD_MASK_OF_RESTRICT_H
#define GUARD_MASK_OF_RESTRICT_H

#include "global.h"

#define MASK_OF_RESTRICT_TRIBUTE_BLOCK 4

u8 IsActivatedMaskOfRestrictZone(const struct DuelCard *zone);
u8 IsMaskOfRestrictActiveOnField(void);
u8 MaskOfRestrictOnField(void);
u8 TryBlockTributeWithMaskOfRestrict(void);

#endif // GUARD_MASK_OF_RESTRICT_H
