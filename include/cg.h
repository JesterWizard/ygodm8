#ifndef CG_H
#define CG_H

#include "constants/event_cg_generated.h"

extern const u8 gEventCgTableCount;

void EventCg_HandleDisplayOpcode(struct ScriptCtx *scriptCtx, u8 cgId, u8 fadeSpeed);
void EventCg_HandleHideOpcode(struct ScriptCtx *scriptCtx, u8 fadeSpeed);
bool8 EventCg_TryConsumeDisplayOpcode(struct ScriptCtx *scriptCtx);
bool8 EventCg_TryConsumeHideOpcode(struct ScriptCtx *scriptCtx);
void EventCg_BeforeExecuteOpcode(struct ScriptCtx *scriptCtx);
void EventCg_AfterExecuteOpcode(struct ScriptCtx *scriptCtx);
void EventCg_OnTextWaitComplete(struct ScriptCtx *scriptCtx);
void EventCg_OnScriptFrameEnd(void);
void EventCg_ForceClose(void);
bool8 EventCg_IsSessionOpen(void);
bool8 EventCg_IsActive(void);
void EventCg_ApplyTextWindowRegs(void);

#endif
