#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "debug_save_anywhere.h"
#include "event_system.h"
#include "overworld.h"

extern u16 gUnk08103264[];

void sub_8052088(u8 obj);
void sub_804F054(int spriteId, int arg1, u8 *dest);
void sub_80551B8(void);
void sub_805339C(void);
void sub_8053404(void);
void sub_804DF5C(int objectId);
void LoadBgOffsets(void);
void LoadOam(void);
void LoadPalettes(void);

static inline void CallThumbVoid(u32 addr) {
  ((void (*)(void))(addr | 1))();
}

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
  EventSystem_AdvanceScriptFrame();
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

LYN_REPLACE_CHECK(sub_8053404);
void sub_8053404__Replacement(void) {
  sub_805339C();
  REG_WINOUT = 0x3D3E;
  OverworldSetRegDispcnt();
  if (EventSystem_ShouldHoldEnterFadeBlack() == TRUE) {
    EventSystem_ApplyEnterFadeBlack();
    return;
  }
  REG_BLDCNT = 0;
}

LYN_REPLACE_CHECK(sub_8053CF0);
void sub_8053CF0__Replacement(u8 obj, s16 x, s16 y, u16 arg3, struct ScriptCtx *script) {
  (void)script;

  SetObjectPosition(obj, x, y, arg3, FALSE, 0);
}

LYN_REPLACE_CHECK(sub_804F1F4);
void sub_804F1F4__Replacement(void) {
  WaitForVBlank();
  CpuFastCopy(gBgVram.cbb4, (void *)0x06010000, 0x2000);
  LoadPalettes();
  EventSystem_ReapplyEnterFadeBlackIfHeld();
}

LYN_REPLACE_CHECK(sub_804F254);
void sub_804F254__Replacement(void) {
  CallThumbVoid(0x0804E618);
  CallThumbVoid(0x0804EBE4);
  sub_80551B8();
  SetVBlankCallback(LoadBgOffsets);
  WaitForVBlank();
  LoadOam();
  CpuFastCopy(gBgVram.cbb4, (void *)0x06010000, 0x2000);
  EventSystem_ReapplyEnterFadeBlackIfHeld();
}

LYN_REPLACE_CHECK(sub_8053D50);
void sub_8053D50__Replacement(u8 obj, u8 arg1, struct ScriptCtx *script) {
  if (gDebugSaveAnywherePendingCapture == TRUE)
    return;

  script->unk86 = 0;
  sub_8053404();
  gOverworld.objects[obj].spriteId = arg1;
  sub_804DF5C(obj);
  sub_804F1F4__Replacement();
}
