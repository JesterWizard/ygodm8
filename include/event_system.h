#ifndef GUARD_EVENT_SYSTEM_H
#define GUARD_EVENT_SYSTEM_H

#include "overworld.h"

typedef struct {
  const struct Script *vanilla;
  const struct Script *replacement;
} EventScriptReplacement;

typedef struct {
  u8 mapId;
  u8 mapState;
  struct Script *script;
} MapEventBinding;

typedef struct {
  u8 mapId;
  u8 mapState;
  struct Script *script;
} StorySequenceEntry;

extern const EventScriptReplacement gEventScriptReplacements[];
extern const unsigned gEventScriptReplacementCount;
extern const MapEventBinding gMapEventBindings[];
extern const unsigned gMapEventBindingCount;
extern const StorySequenceEntry gStorySequence[];
extern const unsigned gStorySequenceCount;
extern const u8 gStoryStartConfigured;
extern const u8 gStoryStartMapId;
extern const u8 gStoryStartMapState;
extern const u8 gStoryStartMapConnection;
extern u8 gStorySequenceProgress;
extern u8 gStorySequenceEnterActive;
extern u8 gStorySequenceSkipLeadingWarp;
extern u8 gStorySequenceHoldFade;
extern const u8 gStorySequenceMode;
extern struct Script gEventScriptNopEnterNode;

const struct Script *EventSystem_ResolveScript(const struct Script *script);
struct Script *EventSystem_GetMapEnterScript(u8 mapId, u8 mapState);
struct Script *EventSystem_GetHouseSavePromptScript(void);
bool8 EventSystem_IsStoryScene(u8 mapId, u8 mapState);
struct Script *EventSystem_ResolveMapEnterScript(struct Script *script);

void EventSystem_GetInitialWarp(u16 *mapId, u16 *mapState, u16 *connection);

void EventSystem_BeginStoryEnter(void);
void EventSystem_ResetStoryEnterState(void);
bool8 EventSystem_IsStoryEnterActive(void);
void EventSystem_OnStoryEnterWarped(void);
bool8 EventSystem_TryCompleteStoryEnter(void);
u8 EventSystem_GetLeadingWarpSkipBytes(struct Script *script);
bool8 EventSystem_ShouldDeferStoryEnterFadeOut(void);
bool8 EventSystem_ShouldHoldEnterFadeBlack(void);
void EventSystem_ApplyEnterFadeBlack(void);
void EventSystem_ClearEnterFade(void);
void EventSystem_SyncHiddenOverworldGfx(void);
bool8 EventSystem_TryConsumeWarpOpcode(struct ScriptCtx *scriptCtx);
bool8 EventSystem_TryConsumeFadeInOpcode(struct ScriptCtx *scriptCtx);
bool8 EventSystem_TryConsumeFadeOutOpcode(struct ScriptCtx *scriptCtx);
void EventSystem_FadeOutScreen(u8 speed);
void EventSystem_AdvanceScriptFrame(void);
void EventSystem_ReapplyEnterFadeBlackIfHeld(void);
bool8 EventSystem_TryConsumeSetObjectPositionOpcode(struct ScriptCtx *scriptCtx);

#endif
