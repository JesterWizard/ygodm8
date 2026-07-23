#include "global.h"
#include "configs/runtime.h"
#include "debug_save_anywhere.h"
#include "event_system.h"
#include "gfx_reg_buffers.h"
#include "match_setter.h"
#include "overworld.h"

extern void (*g20245AC)(int, u8 *, int);
extern u8 gDebugSaveAnywhereDataFlashPrimary[];
extern u8 gDebugSaveAnywhereDataFlashBackup[];
int sub_80588C4(u8 *, int, int);
void sub_804F580(void);
void sub_804F598(void);
void sub_804EEE0(void);
void OverworldRunEndFrame(void);

static struct DebugSaveAnywhereData *DebugSaveAnywhereData(void) {
  return (struct DebugSaveAnywhereData *)gDebugSaveAnywhereData;
}

static void DebugSaveAnywhere_LoadFromFlash(int address) {
  if (g20245AC == NULL)
    return;

  g20245AC(address, gDebugSaveAnywhereData, sizeof(struct DebugSaveAnywhereData));

  if (DebugSaveAnywhereData()->magic == DEBUG_SAVE_ANYWHERE_MAGIC) {
    gDebugSaveAnywhereRestorePending = TRUE;
    gDebugSaveAnywhereApplyCoordsPending = TRUE;
  }
}

static void DebugSaveAnywhere_SyncFollowersToPlayer(void) {
  u8 i;

  for (i = 13; i <= 14; i++) {
    if (gOverworld.objects[i].spriteId >= 0) {
      gOverworld.objects[i].x = gOverworld.objects[0].x;
      gOverworld.objects[i].y = gOverworld.objects[0].y;
      gOverworld.objects[i].direction = gOverworld.objects[0].direction;
      sub_8052088(i);
    }
  }
}

void DebugSaveAnywhere_Reset(void) {
  DebugSaveAnywhereData()->magic = 0;
  gDebugMenuPendingSaveAnywhere = FALSE;
  gDebugSaveAnywherePendingCapture = FALSE;
  gDebugSaveAnywhereRestorePending = FALSE;
  gDebugSaveAnywhereApplyCoordsPending = FALSE;
  gDebugSaveAnywhereOpenDialogPending = FALSE;
  gDebugSaveAnywhereOpenDialogReady = FALSE;
}

void DebugSaveAnywhere_ClearSavedPosition(void) {
  DebugSaveAnywhereData()->magic = 0;
  gDebugSaveAnywhereRestorePending = FALSE;
  gDebugSaveAnywhereApplyCoordsPending = FALSE;
}

void DebugSaveAnywhere_CaptureCurrentPosition(void) {
  struct DebugSaveAnywhereData *data = DebugSaveAnywhereData();

  gOverworld.map.unk8 = gOverworld.map.id;
  gOverworld.map.unkA = gOverworld.map.state;

  data->magic = DEBUG_SAVE_ANYWHERE_MAGIC;
  data->mapId = gOverworld.map.id;
  data->mapState = gOverworld.map.state;
  data->mapConnection = gOverworld.map.unkC;
  data->x = (u16)gOverworld.objects[0].x;
  data->y = (u16)gOverworld.objects[0].y;
  data->direction = gOverworld.objects[0].direction;
  gDebugSaveAnywhereRestorePending = FALSE;
  gDebugSaveAnywhereApplyCoordsPending = FALSE;
}

void DebugSaveAnywhere_ApplySavedCoords(void) {
  struct DebugSaveAnywhereData *data;

  if (gDebugSaveAnywhereApplyCoordsPending != TRUE)
    return;

  data = DebugSaveAnywhereData();
  if (data->magic != DEBUG_SAVE_ANYWHERE_MAGIC) {
    gDebugSaveAnywhereApplyCoordsPending = FALSE;
    return;
  }
  if (data->mapId != gOverworld.map.id || data->mapState != gOverworld.map.state) {
    gDebugSaveAnywhereApplyCoordsPending = FALSE;
    return;
  }

  gOverworld.objects[0].x = (s16)data->x;
  gOverworld.objects[0].y = (s16)data->y;
  gOverworld.objects[0].direction = data->direction;
  sub_8052088(0);
  DebugSaveAnywhere_SyncFollowersToPlayer();
  sub_804EEE0();
  gDebugSaveAnywhereApplyCoordsPending = FALSE;
}

void DebugSaveAnywhere_LoadFromFlashPrimary(void) {
  DebugSaveAnywhere_LoadFromFlash((int)&gDebugSaveAnywhereDataFlashPrimary);
}

void DebugSaveAnywhere_LoadFromFlashBackup(void) {
  DebugSaveAnywhere_LoadFromFlash((int)&gDebugSaveAnywhereDataFlashBackup);
}

void DebugSaveAnywhere_SaveToFlashPrimary(void) {
  sub_80588C4(gDebugSaveAnywhereData, (int)&gDebugSaveAnywhereDataFlashPrimary,
              sizeof(struct DebugSaveAnywhereData));
}

void DebugSaveAnywhere_SaveToFlashBackup(void) {
  sub_80588C4(gDebugSaveAnywhereData, (int)&gDebugSaveAnywhereDataFlashBackup,
              sizeof(struct DebugSaveAnywhereData));
}

void DebugMenu_ApplyPendingSaveAnywhere(void) {
  if (gDebugMenuPendingSaveAnywhere != TRUE)
    return;

  gDebugMenuPendingSaveAnywhere = FALSE;
  gDebugSaveAnywhereOpenDialogPending = TRUE;
}

void DebugSaveAnywhere_OpenDialogNow(void) {
  OverworldLoadGraphics();
  sub_804F580();
  sub_804F598();
  MatchSetter_RefreshField();
  LoadObjVRAM();
  LoadPalettes();
  OverworldRunEndFrame();
  gDebugSaveAnywherePendingCapture = TRUE;
  InitiateScript(EventSystem_GetHouseSavePromptScript());
}
