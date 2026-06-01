#include "global.h"
#include "debug_ai_mode.h"

extern void (*g20245AC)(int, u8 *, int);
int sub_80588C4(u8 *, int, int);

static void DebugAiMode_Normalize(void) {
  if (gDebugAiBothSidesMode != DEBUG_AI_MODE_BOTH_SIDES)
    gDebugAiBothSidesMode = DEBUG_AI_MODE_OFF;
}

u8 DebugAiMode_IsBothSides(void) {
  return gDebugAiBothSidesMode == DEBUG_AI_MODE_BOTH_SIDES;
}

void DebugAiMode_SetMode(u8 mode) {
  gDebugAiBothSidesMode =
      mode == DEBUG_AI_MODE_BOTH_SIDES ? DEBUG_AI_MODE_BOTH_SIDES : DEBUG_AI_MODE_OFF;
  DebugAiMode_SaveToFlashPrimary();
  DebugAiMode_SaveToFlashBackup();
}

static void DebugAiMode_LoadFromFlash(int address) {
  if (g20245AC == NULL)
    return;
  g20245AC(address, &gDebugAiBothSidesMode, 1);
  DebugAiMode_Normalize();
}

void DebugAiMode_LoadFromFlashPrimary(void) {
  DebugAiMode_LoadFromFlash((int)&gDebugAiBothSidesModeFlashPrimary);
}

void DebugAiMode_LoadFromFlashBackup(void) {
  DebugAiMode_LoadFromFlash((int)&gDebugAiBothSidesModeFlashBackup);
}

void DebugAiMode_SaveToFlashPrimary(void) {
  sub_80588C4(&gDebugAiBothSidesMode, (int)&gDebugAiBothSidesModeFlashPrimary, 1);
}

void DebugAiMode_SaveToFlashBackup(void) {
  sub_80588C4(&gDebugAiBothSidesMode, (int)&gDebugAiBothSidesModeFlashBackup, 1);
}

void DebugAiMode_Reset(void) {
  gDebugAiBothSidesMode = DEBUG_AI_MODE_OFF;
}
