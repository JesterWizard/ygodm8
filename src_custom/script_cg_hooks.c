#include "global.h"
#include "common-chax.h"
#include "cg.h"
#include "event_system.h"
#include "overworld.h"

typedef void (*ScriptCtxFunc)(struct ScriptCtx *);
typedef void (*SetCurrentScriptFunc)(struct ScriptCtx *, struct Script *);

void sub_80526D0(struct ScriptCtx *scriptCtx);

static inline ScriptCtxFunc ThumbScriptCtxFunc(u32 addr) {
  return (ScriptCtxFunc)(addr | 1);
}

static inline SetCurrentScriptFunc ThumbSetCurrentScript(u32 addr) {
  return (SetCurrentScriptFunc)(addr | 1);
}

LYN_REPLACE_CHECK(sub_80526D0);
void sub_80526D0__Replacement(struct ScriptCtx *scriptCtx) {
  while (1) {
    if (scriptCtx->currentScript.start[scriptCtx->pointer] == 0) {
      struct Script *chooseScript;

      if (!scriptCtx->unk1E)
        chooseScript = scriptCtx->currentScript.unk4;
      else
        chooseScript = scriptCtx->currentScript.unk8;

      scriptCtx->currentScript.start = chooseScript->start;
      scriptCtx->currentScript.unk4 = chooseScript->unk4;
      scriptCtx->currentScript.unk8 = chooseScript->unk8;
      scriptCtx->pointer = 0;
      scriptCtx->unk1E = 0;
      ThumbScriptCtxFunc(0x08053388)(scriptCtx);
    }
    if (scriptCtx->currentScript.start[0] == 0x5D)
      break;

    switch (scriptCtx->unkC) {
    case 0:
      EventCg_BeforeExecuteOpcode(scriptCtx);
      if (EventCg_TryConsumeDisplayOpcode(scriptCtx))
        break;
      if (EventCg_TryConsumeHideOpcode(scriptCtx))
        break;
      if (EventSystem_TryConsumeSetObjectPositionOpcode(scriptCtx))
        break;
      if (EventSystem_TryConsumeFadeInOpcode(scriptCtx))
        break;
      ThumbScriptCtxFunc(0x080527E8)(scriptCtx);
      EventCg_AfterExecuteOpcode(scriptCtx);
      break;
    case 1: {
      u8 prevUnkC = scriptCtx->unkC;
      ThumbScriptCtxFunc(0x08052F60)(scriptCtx);
      if (prevUnkC == 1 && scriptCtx->unkC == 0)
        EventCg_OnTextWaitComplete(scriptCtx);
      break;
    }
    case 2:
      ThumbScriptCtxFunc(0x08053138)(scriptCtx);
      break;
    case 3: {
      u8 prevUnkC = scriptCtx->unkC;
      ThumbScriptCtxFunc(0x08053040)(scriptCtx);
      if (prevUnkC == 3 && scriptCtx->unkC == 0)
        EventCg_OnTextWaitComplete(scriptCtx);
      break;
    }
    }

    if (scriptCtx->unk86 == 1) {
      if (EventCg_IsActive()) {
        EventCg_ApplyTextWindowRegs();
      } else {
        REG_WIN1H = 0x03ED;
        REG_WIN1V = 0x739D;
        (*(vu8 *)(REG_BASE + 0x49)) = 0x3F;
        REG_WINOUT = 0x1D1E;
        OverworldSetRegDispcnt2();
        if (EventSystem_ShouldHoldEnterFadeBlack() == TRUE) {
          EventSystem_ApplyEnterFadeBlack();
        } else {
          REG_BLDCNT = 0xDE;
          REG_BLDY = 7;
        }
      }
    }
    if (!EventCg_IsActive())
      sub_804F218();
    EventCg_OnScriptFrameEnd();

    if (gOverworld.flags & OVERWORLD_FLAG_MAP_TRANSITION)
      break;
  }

  EventCg_ForceClose();

  if (gOverworld.flags & OVERWORLD_FLAG_MAP_TRANSITION) {
    if (EventSystem_IsStoryEnterActive())
      EventSystem_OnStoryEnterWarped();
    return;
  }

  if (EventSystem_ShouldDeferStoryEnterFadeOut())
    return;

  if (EventSystem_ShouldHoldEnterFadeBlack() == TRUE)
    return;

  PlayOverworldMusic();
  scriptCtx->portraitId = PORTRAIT_NONE;
  scriptCtx->unk84 = 0;
  DisplayPortrait(scriptCtx);
  REG_WINOUT = 0x3D3E;
  OverworldSetRegDispcnt();
  REG_BLDCNT = 0;
}
