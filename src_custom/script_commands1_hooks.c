#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "debug_save_anywhere.h"
#include "event_system.h"
#include "overworld.h"

extern u16 gUnk08103264[];

void sub_8052088(u8 obj);
void sub_804F054(int spriteId, int arg1, u8 *dest);
void sub_804F218(void);
void sub_8053404(void);
void sub_804DF5C(int objectId);
void sub_804F1F4(void);

static void SetObjectPosition(u8 obj, s16 x, s16 y, u8 frame, bool8 setDirection, u8 direction) {
  gOverworld.objects[obj].x = x;
  gOverworld.objects[obj].y = y;
  gOverworld.objects[obj].wander = 0;
  if (setDirection == TRUE)
    gOverworld.objects[obj].direction = direction;
  sub_8052088(obj);
  sub_804F054(gOverworld.objects[obj].spriteId,
              gOverworld.objects[obj].direction * 3 + frame,
              gBgVram.cbb4 + gUnk08103264[obj] * 32);

  if (EventSystem_ShouldHoldEnterFadeBlack() == TRUE) {
    EventSystem_SyncHiddenOverworldGfx();
    EventSystem_ApplyEnterFadeBlack();
  } else {
    sub_804F218();
  }
}

bool8 EventSystem_TryConsumeSetObjectPositionOpcode(struct ScriptCtx *scriptCtx) {
  const u8 *script = scriptCtx->currentScript.start;
  u32 pointer = scriptCtx->pointer;

  if (gRuntimeConfig.enable_custom_events != TRUE)
    return FALSE;

  if (script[pointer] != 0x7C || script[pointer + 1] != 'C')
    return FALSE;

  SetObjectPosition(script[pointer + 2], script[pointer + 3], script[pointer + 4],
                    script[pointer + 5], TRUE, script[pointer + 6]);
  scriptCtx->pointer += 7;
  return TRUE;
}

LYN_REPLACE_CHECK(sub_8053CF0);
void sub_8053CF0__Replacement(u8 obj, s16 x, s16 y, u16 arg3, struct ScriptCtx *script) {
  (void)script;

  SetObjectPosition(obj, x, y, arg3, FALSE, 0);
}

LYN_REPLACE_CHECK(sub_8053D50);
void sub_8053D50__Replacement(u8 obj, u8 arg1, struct ScriptCtx *script) {
  (void)obj;
  (void)arg1;

  if (gDebugSaveAnywherePendingCapture == TRUE)
    return;

  script->unk86 = 0;
  sub_8053404();
  gOverworld.objects[obj].spriteId = arg1;
  sub_804DF5C(obj);
  sub_804F1F4();
}
