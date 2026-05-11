#pragma once

#include "duel.h"
#include "card.h"
#include "constants/card_ids.h"
#include "configs/runtime.h"

extern unsigned char LowLevelAntePrompt (void);
extern void sub_800C32C (void);
extern void sub_800C378 (void);
extern unsigned char TrySelectingAnte (void);

#define NORMAL_CARD 0
#define EFFECT_CARD 1
#define FUSION_CARD 2
#define SPELL_CARD 3
#define TRAP_CARD 4
#define RITUAL_CARD 5