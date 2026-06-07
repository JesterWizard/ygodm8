#include "global.h"
#include "event_system.h"
#include "configs/runtime.h"
#include "debug_save_anywhere.h"
#include "gfx_reg_buffers.h"
#include "overworld.h"
#include "overworld_debug_overlay.h"
#include "cg.h"

#define ENTER_FADE_BLACK_BLDCNT 0xFF
#define ENTER_FADE_BLACK_BLDY   16

#include "generated/event_script_replacements.inc"

typedef void (*SetCurrentScriptFunc)(struct ScriptCtx *, struct Script *);
typedef void (*ScriptCtxFunc)(struct ScriptCtx *);

#define STORY_WARP_OPCODE_SIZE 6

static inline SetCurrentScriptFunc ThumbSetCurrentScript(u32 addr) {
  return (SetCurrentScriptFunc)(addr | 1);
}

static inline ScriptCtxFunc ThumbScriptCtxFunc(u32 addr) {
  return (ScriptCtxFunc)(addr | 1);
}

static bool8 IsMapEnterScript(struct Script *script) {
  return script == gOverworld.unk1F4[gOverworld.map.unk4];
}

static bool8 ScriptStartsWithWarp(struct Script *script, u16 *mapId, u16 *mapState) {
  u8 *bytes;

  if (script == NULL || script->start == NULL)
    return FALSE;

  bytes = script->start;
  if (bytes[0] != 0x7C || bytes[1] != '5')
    return FALSE;

  *mapId = bytes[2];
  *mapState = bytes[3];
  return TRUE;
}

void sub_804EEE0(void);
void sub_80526D0__Replacement(struct ScriptCtx *scriptCtx);

const struct Script *EventSystem_ResolveScript(const struct Script *script) {
  unsigned i;

  for (i = 0; i < gEventScriptReplacementCount; i++)
    if (gEventScriptReplacements[i].vanilla == script)
      return gEventScriptReplacements[i].replacement;

  return script;
}

struct Script *EventSystem_GetMapEnterScript(u8 mapId, u8 mapState) {
  unsigned i;

  for (i = 0; i < gMapEventBindingCount; i++) {
    if (gMapEventBindings[i].mapId == mapId && gMapEventBindings[i].mapState == mapState)
      return gMapEventBindings[i].script;
  }

  return NULL;
}

bool8 EventSystem_IsStoryScene(u8 mapId, u8 mapState) {
  unsigned i;

  for (i = 0; i < gStorySequenceCount; i++) {
    if (gStorySequence[i].mapId == mapId && gStorySequence[i].mapState == mapState)
      return TRUE;
  }

  return FALSE;
}

void EventSystem_BeginStoryEnter(void) {
  gStorySequenceEnterActive = TRUE;
}

void EventSystem_ResetStoryEnterState(void) {
  gStorySequenceEnterActive = FALSE;
  gStorySequenceSkipLeadingWarp = FALSE;
  gStorySequenceHoldFade = FALSE;
}

bool8 EventSystem_IsStoryEnterActive(void) {
  return gStorySequenceEnterActive;
}

void EventSystem_OnStoryEnterWarped(void) {
  gStorySequenceEnterActive = TRUE;
  gStorySequenceSkipLeadingWarp = TRUE;
  gStorySequenceHoldFade = TRUE;
}

void sub_804F218(void);
void sub_80551B8(void);

typedef void (*VoidFunc)(void);

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

void EventSystem_SyncHiddenOverworldGfx(void) {
  CallThumbVoid(0x0804E618);
  CallThumbVoid(0x0804EBE4);
  sub_80551B8();
  LoadObjVRAM();
  LoadOam();
  CpuCopy32(gBgVram.sbb1B, (void *)0x0600D800, 0xE20);
}

void EventSystem_ApplyEnterFadeBlack(void) {
  REG_BLDCNT = ENTER_FADE_BLACK_BLDCNT;
  REG_BLDY = ENTER_FADE_BLACK_BLDY;
  gBLDCNT = ENTER_FADE_BLACK_BLDCNT;
  gBLDY = ENTER_FADE_BLACK_BLDY;
  if (gRuntimeConfig.enable_custom_events == TRUE)
    gStorySequenceHoldFade = TRUE;
}

void EventSystem_ClearEnterFade(void) {
  REG_BLDCNT = 0;
  REG_BLDY = 0;
  gBLDCNT = 0;
  gBLDY = 0;
}

static void EventSystem_FadeFromBlack(u8 speed) {
  int i, temp;

  OverworldSetRegDispcnt();
  REG_BLDCNT = ENTER_FADE_BLACK_BLDCNT;
  REG_WINOUT = 0x3D3E;
  gBLDCNT = ENTER_FADE_BLACK_BLDCNT;
  REG_BLDY = ENTER_FADE_BLACK_BLDY;
  gBLDY = ENTER_FADE_BLACK_BLDY;
  for (i = ENTER_FADE_BLACK_BLDY; i >= 0; i--) {
    REG_BLDY = i;
    gBLDY = i;
    temp = speed;
    while (--temp != -1)
      sub_804F218();
  }
  EventSystem_ClearEnterFade();
}

static void EventSystem_FadeInEnterScene(u8 speed) {
  EventSystem_SyncHiddenOverworldGfx();
  EventSystem_FadeFromBlack(speed);
}

void EventSystem_FadeOutScreen(u8 speed) {
  EventSystem_FadeFromBlack(speed);
}

void EventSystem_ReapplyEnterFadeBlackIfHeld(void) {
  if (EventSystem_ShouldHoldEnterFadeBlack() == TRUE)
    EventSystem_ApplyEnterFadeBlack();
}

void EventSystem_AdvanceScriptFrame(void) {
  if (EventSystem_ShouldHoldEnterFadeBlack() == TRUE) {
    EventSystem_SyncHiddenOverworldGfx();
    EventSystem_ApplyEnterFadeBlack();
    return;
  }

  sub_804F218();
}

void sub_80523EC(u16 id, u16 state, u16 connection);

bool8 EventSystem_TryConsumeWarpOpcode(struct ScriptCtx *scriptCtx) {
  const u8 *script = scriptCtx->currentScript.start;
  u32 pointer = scriptCtx->pointer;

  if (gRuntimeConfig.enable_custom_events != TRUE)
    return FALSE;

  if (script[pointer] != 0x7C || script[pointer + 1] != '5')
    return FALSE;

  if (EventSystem_ShouldHoldEnterFadeBlack() == TRUE ||
      gBLDY >= ENTER_FADE_BLACK_BLDY || REG_BLDY >= ENTER_FADE_BLACK_BLDY) {
    gStorySequenceHoldFade = TRUE;
    EventSystem_ApplyEnterFadeBlack();
  }

  gOverworld.flags |= OVERWORLD_FLAG_MAP_TRANSITION;
  sub_80523EC(script[pointer + 2], script[pointer + 3], script[pointer + 4]);
  EventSystem_ReapplyEnterFadeBlackIfHeld();
  scriptCtx->pointer += STORY_WARP_OPCODE_SIZE;
  return TRUE;
}

bool8 EventSystem_TryConsumeFadeInOpcode(struct ScriptCtx *scriptCtx) {
  const u8 *script = scriptCtx->currentScript.start;
  u32 pointer = scriptCtx->pointer;

  if (gRuntimeConfig.enable_custom_events != TRUE)
    return FALSE;

  if (script[pointer] != 0x7C || script[pointer + 1] != 'B')
    return FALSE;

  gStorySequenceHoldFade = FALSE;
  EventSystem_FadeInEnterScene(script[pointer + 2]);
  scriptCtx->pointer += 3;
  return TRUE;
}

bool8 EventSystem_TryConsumeFadeOutOpcode(struct ScriptCtx *scriptCtx) {
  const u8 *script = scriptCtx->currentScript.start;
  u32 pointer = scriptCtx->pointer;

  if (gRuntimeConfig.enable_custom_events != TRUE)
    return FALSE;

  if (script[pointer] != 0x7C || script[pointer + 1] != 'D')
    return FALSE;

  EventSystem_FadeOutScreen(script[pointer + 2]);
  scriptCtx->pointer += 3;
  return TRUE;
}

bool8 EventSystem_ShouldDeferStoryEnterFadeOut(void) {
  if (gRuntimeConfig.enable_custom_events != TRUE)
    return FALSE;

  if (gStorySequenceMode != TRUE || gStorySequenceEnterActive != TRUE)
    return FALSE;

  return gStorySequenceProgress + 1 < gStorySequenceCount;
}

bool8 EventSystem_ShouldHoldEnterFadeBlack(void) {
  return gRuntimeConfig.enable_custom_events == TRUE && gStorySequenceHoldFade == TRUE;
}

bool8 EventSystem_TryCompleteStoryEnter(void) {
  if (gStorySequenceEnterActive != TRUE)
    return FALSE;

  EventSystem_ResetStoryEnterState();

  if (gStorySequenceProgress < gStorySequenceCount)
    gStorySequenceProgress++;

  return TRUE;
}

u8 EventSystem_GetLeadingWarpSkipBytes(struct Script *script) {
  u16 warpMapId;
  u16 warpMapState;

  if (!ScriptStartsWithWarp(script, &warpMapId, &warpMapState))
    return 0;

  if (gStorySequenceSkipLeadingWarp == TRUE) {
    gStorySequenceSkipLeadingWarp = FALSE;
    gStorySequenceHoldFade = TRUE;
    return STORY_WARP_OPCODE_SIZE;
  }

  if (warpMapId == gOverworld.map.id && warpMapState == gOverworld.map.state)
    return STORY_WARP_OPCODE_SIZE;

  return 0;
}

struct Script *EventSystem_ResolveMapEnterScript(struct Script *script) {
  const StorySequenceEntry *pending;

  if (!IsMapEnterScript(script))
    return (struct Script *)EventSystem_ResolveScript((const struct Script *)script);

  if (gRuntimeConfig.enable_custom_events == TRUE && gStorySequenceMode) {
    if (gStorySequenceProgress < gStorySequenceCount) {
      pending = &gStorySequence[gStorySequenceProgress];

      if (gStorySequenceEnterActive == TRUE && gStorySequenceSkipLeadingWarp == TRUE) {
        EventSystem_BeginStoryEnter();
        gStorySequenceHoldFade = TRUE;
        return pending->script;
      }

      if (pending->mapId == gOverworld.map.id && pending->mapState == gOverworld.map.state) {
        EventSystem_BeginStoryEnter();
        gStorySequenceHoldFade = TRUE;
        return pending->script;
      }
    }
    return &gEventScriptNopEnterNode;
  }

  {
    struct Script *mapEnterScript;

    mapEnterScript = EventSystem_GetMapEnterScript(gOverworld.map.id, gOverworld.map.state);
    if (mapEnterScript != NULL)
      return mapEnterScript;
  }

  return script;
}

struct Script *EventSystem_GetHouseSavePromptScript(void) {
  return &sEventScript_map_09_state_00_08E621E4Node;
}

void EventSystem_GetInitialWarp(u16 *mapId, u16 *mapState, u16 *connection) {
  if (gStorySequenceMode && gStorySequenceCount != 0) {
    if (gStoryStartConfigured) {
      *mapId = gStoryStartMapId;
      *mapState = gStoryStartMapState;
      *connection = gStoryStartMapConnection;
    } else {
      *mapId = gStorySequence[0].mapId;
      *mapState = gStorySequence[0].mapState;
      *connection = 0;
    }
    if (gRuntimeConfig.enable_custom_events == TRUE)
      gStorySequenceHoldFade = TRUE;
    return;
  }

  if (gRuntimeConfig.use_custom_start_map == TRUE) {
    *mapId = gRuntimeConfig.custom_start_map_id;
    *mapState = gRuntimeConfig.custom_start_map_state;
    *connection = gRuntimeConfig.custom_start_map_connection;
    return;
  }

  *mapId = LOCATION_PLAYER_HOUSE_INSIDE;
  *mapState = 1;
  *connection = 0;
}

static void InitiateScriptCtx(struct ScriptCtx *scriptCtx) {
  scriptCtx->portraitId = PORTRAIT_NONE;
  scriptCtx->pointer = 0;
  scriptCtx->unk1E = 0;
  scriptCtx->unk8 = 0;
  scriptCtx->unkC = 0;
  scriptCtx->unkD = 1;
  scriptCtx->unk1C = 0;
  scriptCtx->unk78 = 0;
  scriptCtx->unk74 = 0;
  scriptCtx->unk76 = 0;
  scriptCtx->unk7A = 0x1D;
  scriptCtx->unk7C = 1;
  scriptCtx->unk7E = 3;
  scriptCtx->unk80 = 1;
  scriptCtx->unk82 = 0;
  scriptCtx->unk86 = 0;
}

static void RunScript(struct ScriptCtx *scriptCtx, struct Script *script) {
  InitiateScriptCtx(scriptCtx);
  scriptCtx->pointer = EventSystem_GetLeadingWarpSkipBytes(script);
  if (EventSystem_ShouldHoldEnterFadeBlack() == TRUE)
    EventSystem_ApplyEnterFadeBlack();
  ThumbSetCurrentScript(0x08053274)(scriptCtx, script);
  ThumbScriptCtxFunc(0x080532A8)(scriptCtx);
  if (EventSystem_ShouldHoldEnterFadeBlack() == TRUE)
    EventSystem_ApplyEnterFadeBlack();
  sub_80526D0__Replacement(scriptCtx);
}

LYN_REPLACE_CHECK(InitiateScript);
void InitiateScript__Replacement(struct Script *script) {
  struct ScriptCtx scriptCtx;
  bool8 saveAnywhereDialog = (gDebugSaveAnywherePendingCapture == TRUE);
  bool8 chainNextStoryScene = FALSE;

  for (;;) {
    if (chainNextStoryScene) {
      chainNextStoryScene = FALSE;

      if (gStorySequenceProgress >= gStorySequenceCount)
        break;

      script = gStorySequence[gStorySequenceProgress].script;
      gStorySequenceHoldFade = TRUE;
      EventSystem_BeginStoryEnter();
    } else {
      script = EventSystem_ResolveMapEnterScript(script);
    }

    RunScript(&scriptCtx, script);

    if (gOverworld.flags & OVERWORLD_FLAG_MAP_TRANSITION)
      break;

    if (EventSystem_TryCompleteStoryEnter()) {
      if (gRuntimeConfig.enable_custom_events == TRUE && gStorySequenceMode &&
          gStorySequenceProgress < gStorySequenceCount) {
        gStorySequenceHoldFade = TRUE;
        EventSystem_ApplyEnterFadeBlack();
        chainNextStoryScene = TRUE;
      } else {
        break;
      }
      continue;
    }

    break;
  }

  if (saveAnywhereDialog != TRUE)
    DebugSaveAnywhere_ApplySavedCoords();

  if (saveAnywhereDialog == TRUE) {
    gDebugSaveAnywherePendingCapture = FALSE;
    OverworldLoadGraphics();
    sub_804EEE0();
  } else if (gOverworld.flags & OVERWORLD_FLAG_MAP_TRANSITION) {
    EventCg_ForceClose();
  } else {
    EventCg_ForceClose();
    if (EventSystem_ShouldHoldEnterFadeBlack() != TRUE) {
      OverworldOverlay_RestoreDisplayRegs();
      OverworldSetRegDispcnt();
    }
  }

  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE && saveAnywhereDialog != TRUE)
    OverworldOverlay_Refresh();

  scriptCtx.portraitId = PORTRAIT_NONE;
  scriptCtx.pointer = 0;
  scriptCtx.unk8 = 0;
}
