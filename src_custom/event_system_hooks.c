#include "global.h"
#include "event_system.h"
#include "configs/runtime.h"
#include "debug_save_anywhere.h"
#include "overworld.h"
#include "overworld_debug_overlay.h"
#include "cg.h"

#include "generated/event_script_replacements.inc"

extern const u32 g82AD2D0[];
extern u16 g82AD48C[];

typedef void (*SetCurrentScriptFunc)(struct ScriptCtx *, struct Script *);
typedef void (*ScriptCtxFunc)(struct ScriptCtx *);

static inline SetCurrentScriptFunc ThumbSetCurrentScript(u32 addr) {
  return (SetCurrentScriptFunc)(addr | 1);
}

static inline ScriptCtxFunc ThumbScriptCtxFunc(u32 addr) {
  return (ScriptCtxFunc)(addr | 1);
}

void sub_804EEE0(void);
void sub_80526D0__Replacement(struct ScriptCtx *scriptCtx);

const struct Script *EventSystem_ResolveScript(const struct Script *script) {
  unsigned i;

  if (gRuntimeConfig.enable_custom_events != TRUE)
    return script;

  for (i = 0; i < gEventScriptReplacementCount; i++)
    if (gEventScriptReplacements[i].vanilla == script)
      return gEventScriptReplacements[i].replacement;

  return script;
}

struct Script *EventSystem_GetHouseSavePromptScript(void) {
  return &sEventScript_map_09_state_00_08E621E4Node;
}

LYN_REPLACE_CHECK(InitiateScript);
void InitiateScript__Replacement(struct Script *script) {
  struct ScriptCtx scriptCtx;
  bool8 saveAnywhereDialog = (gDebugSaveAnywherePendingCapture == TRUE);

  script = (struct Script *)EventSystem_ResolveScript(script);

  EventCg_ForceClose();
  LZ77UnCompWram(g82AD2D0, (void *)gBgVram.sbb1B);
  CpuCopy16(g82AD48C, (void *)gBgVram.sbb1D, 0x500);
  REG_BLDCNT = 0;
  REG_BLDALPHA = 0;
  REG_BLDY = 0;

  scriptCtx.portraitId = PORTRAIT_NONE;
  scriptCtx.pointer = 0;
  scriptCtx.unk1E = 0;
  scriptCtx.unk8 = 0;
  scriptCtx.unkC = 0;
  scriptCtx.unkD = 1;
  scriptCtx.unk1C = 0;
  scriptCtx.unk78 = 0;
  scriptCtx.unk74 = 0;
  scriptCtx.unk76 = 0;
  scriptCtx.unk7A = 0x1D;
  scriptCtx.unk7C = 1;
  scriptCtx.unk7E = 3;
  scriptCtx.unk80 = 1;
  scriptCtx.unk82 = 0;
  scriptCtx.unk86 = 0;
  ThumbSetCurrentScript(0x08053274)(&scriptCtx, script);
  ThumbScriptCtxFunc(0x080532A8)(&scriptCtx);
  sub_80526D0__Replacement(&scriptCtx);

  if (saveAnywhereDialog != TRUE)
    DebugSaveAnywhere_ApplySavedCoords();

  if (saveAnywhereDialog == TRUE) {
    gDebugSaveAnywherePendingCapture = FALSE;
    OverworldLoadGraphics();
    sub_804EEE0();
  } else {
    EventCg_ForceClose();
    OverworldOverlay_RestoreDisplayRegs();
    OverworldSetRegDispcnt();
  }

  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE && saveAnywhereDialog != TRUE)
    OverworldOverlay_Refresh();

  scriptCtx.portraitId = PORTRAIT_NONE;
  scriptCtx.pointer = 0;
  scriptCtx.unk8 = 0;
}
