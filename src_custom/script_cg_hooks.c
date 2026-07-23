#include "global.h"
#include "common-chax.h"
#include "cg.h"
#include "millennium_items.h"
#include "overworld.h"

void sub_80526D0(struct ScriptCtx *scriptCtx);
void sub_804F218(void);
void DisplayPortrait(struct ScriptCtx *scriptCtx);
void PlayOverworldMusic(void);

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
      /* No CallThumb into statics — MyBoy dies on that pattern. */
      sub_8053388(scriptCtx);
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
      if (MillenniumItems_TryConsumeOpcode(scriptCtx))
        break;
      sub_80527E8(scriptCtx);
      EventCg_AfterExecuteOpcode(scriptCtx);
      break;
    case 1: {
      u8 prevUnkC = scriptCtx->unkC;
      sub_8052F60(scriptCtx);
      if (prevUnkC == 1 && scriptCtx->unkC == 0)
        EventCg_OnTextWaitComplete(scriptCtx);
      break;
    }
    case 2:
      sub_8053138(scriptCtx);
      break;
    case 3: {
      u8 prevUnkC = scriptCtx->unkC;
      sub_8053040(scriptCtx);
      if (prevUnkC == 3 && scriptCtx->unkC == 0)
        EventCg_OnTextWaitComplete(scriptCtx);
      break;
    }
    }

    if (EventCg_IsActive()) {
      EventCg_ApplyPortraitSceneRegs(scriptCtx);
    } else if (scriptCtx->unk86 == 1) {
      REG_WIN1H = 0x03ED;
      REG_WIN1V = 0x739D;
      (*(vu8 *)(REG_BASE + 0x49)) = 0x3F;
      REG_WINOUT = 0x1D1E;
      OverworldSetRegDispcnt2();
      REG_BLDCNT = 0xDE;
      REG_BLDY = 7;
    }
    sub_804F218();
    EventCg_OnScriptFrameEnd(scriptCtx);
  }

  EventCg_ForceClose();

  if (gOverworld.flags & OVERWORLD_FLAG_MAP_TRANSITION)
    return;

  PlayOverworldMusic();
  scriptCtx->portraitId = PORTRAIT_NONE;
  scriptCtx->unk84 = 0;
  DisplayPortrait(scriptCtx);
  REG_WINOUT = 0x3D3E;
  OverworldSetRegDispcnt();
  REG_BLDCNT = 0;
}
