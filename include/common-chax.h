#pragma once

#include "global.h"
#include "ai.h"
#include "duel.h"
#include "card.h"
#include "card_shop.h"
#include "overworld.h"
#include "constants/card_ids.h"
#include "constants/card_enums.h"
#include "constants/music_ids.h"
#include "constants/monster_effects.h"
#include "constants/spell_effects.h"
#include "configs/runtime.h"

extern unsigned char LowLevelAntePrompt (void);
extern void sub_800C32C (void);
extern void sub_800C378 (void);
extern unsigned char TrySelectingAnte (void);


extern void NoCashGBAPrint(const char *pBuf);
extern void NoCashGBAPrintf(const char *pBuf, ...);

extern s16 GetTalkingUnitSprite(void);
extern s8 GetObjectIdInFrontOfPlayer(u8 x, u8 y, u8 playerDirection);
extern void DisplayPortrait (struct ScriptCtx* scriptCtx);