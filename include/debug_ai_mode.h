#ifndef GUARD_DEBUG_AI_MODE_H
#define GUARD_DEBUG_AI_MODE_H

#include "gba/types.h"

#define DEBUG_AI_MODE_OFF 0
#define DEBUG_AI_MODE_BOTH_SIDES 1

extern u8 gDebugAiBothSidesMode;
extern u8 gDebugAiBothSidesModeFlashPrimary;
extern u8 gDebugAiBothSidesModeFlashBackup;

u8 DebugAiMode_IsBothSides(void);
void DebugAiMode_SetMode(u8 mode);
void DebugAiMode_LoadFromFlashPrimary(void);
void DebugAiMode_LoadFromFlashBackup(void);
void DebugAiMode_SaveToFlashPrimary(void);
void DebugAiMode_SaveToFlashBackup(void);
void DebugAiMode_Reset(void);

#endif
