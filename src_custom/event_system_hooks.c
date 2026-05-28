#include "global.h"
#include "event_system.h"
#include "configs/runtime.h"
#include "overworld.h"
#include "overworld_debug_overlay.h"

#include "generated/event_script_replacements.inc"

typedef void (*SetCurrentScriptFunc)(struct ScriptCtx *, struct Script *);
typedef void (*ScriptCtxFunc)(struct ScriptCtx *);

static inline SetCurrentScriptFunc ThumbSetCurrentScript(u32 addr) {
  return (SetCurrentScriptFunc)(addr | 1);
}

static inline ScriptCtxFunc ThumbScriptCtxFunc(u32 addr) {
  return (ScriptCtxFunc)(addr | 1);
}

const struct Script *EventSystem_ResolveScript(const struct Script *script) {
  unsigned i;

  for (i = 0; i < gEventScriptReplacementCount; i++)
    if (gEventScriptReplacements[i].vanilla == script)
      return gEventScriptReplacements[i].replacement;

  return script;
}

LYN_REPLACE_CHECK(InitiateScript);
void InitiateScript__Replacement(struct Script *script) {
  struct ScriptCtx scriptCtx;

  script = (struct Script *)EventSystem_ResolveScript(script);

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
  ThumbScriptCtxFunc(0x080526D0)(&scriptCtx);

  OverworldOverlay_RestoreDisplayRegs();
  OverworldSetRegDispcnt();

  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE)
    OverworldOverlay_Refresh();

  scriptCtx.portraitId = PORTRAIT_NONE;
  scriptCtx.pointer = 0;
  scriptCtx.unk8 = 0;
}
