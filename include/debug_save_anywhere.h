#ifndef GUARD_DEBUG_SAVE_ANYWHERE_H
#define GUARD_DEBUG_SAVE_ANYWHERE_H

#include "gba/types.h"

#define DEBUG_SAVE_ANYWHERE_MAGIC 0x5A

struct DebugSaveAnywhereData {
  u8 magic;
  u8 direction;
  u16 mapId;
  u16 mapState;
  u16 mapConnection;
  u16 x;
  u16 y;
};

extern u8 gDebugSaveAnywhereData[];
extern u8 gDebugMenuPendingSaveAnywhere;
extern u8 gDebugSaveAnywherePendingCapture;
extern u8 gDebugSaveAnywhereRestorePending;
extern u8 gDebugSaveAnywhereApplyCoordsPending;
extern u8 gDebugSaveAnywhereOpenDialogPending;
extern u8 gDebugSaveAnywhereOpenDialogReady;
extern u8 gDebugSaveAnywherePendingCapture;

void DebugSaveAnywhere_Reset(void);
void DebugSaveAnywhere_ClearSavedPosition(void);
void DebugSaveAnywhere_CaptureCurrentPosition(void);
void DebugSaveAnywhere_ApplySavedCoords(void);
void DebugSaveAnywhere_LoadFromFlashPrimary(void);
void DebugSaveAnywhere_LoadFromFlashBackup(void);
void DebugSaveAnywhere_SaveToFlashPrimary(void);
void DebugSaveAnywhere_SaveToFlashBackup(void);
void DebugMenu_ApplyPendingSaveAnywhere(void);
void DebugSaveAnywhere_OpenDialogNow(void);
void OverworldRunEndFrame(void);

#endif
