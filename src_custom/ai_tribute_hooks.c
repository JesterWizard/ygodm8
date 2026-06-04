#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "ai_decision.h"
#include "configs/runtime.h"
#include "mask_of_restrict.h"

struct AI_Command {
  u16 action;
  u8 zone1Position;
  u8 zone2Position;
  u8 zone3Position;
  u8 zone4Position;
  u8 zone5Position;
  u8 zone6Position;
};

extern struct AI_Command sAI_Command;
extern void (*g8DFF600[])(void);
void sub_803FD14(void);
void UpdateDuelGfxExceptField(void);
void sub_800E0D4(void);
void WaitForVBlank(void);
u16 RandRangeU16(u16 min, u16 max);

static u8 TryBlockAiTributeSummonAction(void)
{
  if (!IsAiTributeSummonAction(sAI_Command.action))
    return FALSE;

  if (!TryBlockTributeWithMaskOfRestrict())
    return FALSE;

  AiMemory_NotifyBlockedTribute();
  PlayMusic(SFX_TRAP_TRIGGERED);
  UpdateDuelGfxExceptField();
  return TRUE;
}

static void AiTempoMaybeDelayBeforeAction(void)
{
  u8 i;
  u8 frames;

  if (gRuntimeConfig.enable_smarter_ai != TRUE)
    return;

  if (!AiAction_IsHighImpact(sAI_Command.action))
    return;

  frames = 8 + (RandRangeU16(0, 7));
  for (i = 0; i < frames; i++)
    WaitForVBlank();
}

LYN_REPLACE_CHECK(sub_800E0D4);
void sub_800E0D4__Replacement(void)
{
  if (TryBlockAiTributeSummonAction())
    return;

  AiTempoMaybeDelayBeforeAction();
  sub_803FD14();
  g8DFF600[sAI_Command.action]();
  AiMemory_RecordExecutedAction();
}
