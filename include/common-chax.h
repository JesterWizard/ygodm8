#pragma once

#include "duel.h"
#include "card.h"
#include "constants/card_ids.h"
#include "constants/card_enums.h"
#include "configs/runtime.h"

extern unsigned char LowLevelAntePrompt (void);
extern void sub_800C32C (void);
extern void sub_800C378 (void);
extern unsigned char TrySelectingAnte (void);