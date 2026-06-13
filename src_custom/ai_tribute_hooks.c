#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "ai_decision.h"
#include "configs/runtime.h"
#include "mask_of_restrict.h"
#include "summon_tribute.h"
#include "great_maju_garzett.h"

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

static void RecordAiSummonTributeCount(void)
{
  switch (sAI_Command.action) {
  case AI_ACTION_0_TRIBUTE_SUMMON:
  case AI_ACTION_PERM_CARD_0_TRIBUTE_SUMMON:
    SetPendingSummonTributeCount(0);
    return;
  case AI_ACTION_1_TRIBUTE_SUMMON:
  case AI_ACTION_PERM_CARD_1_TRIBUTE_SUMMON:
    SetPendingSummonTributeCount(1);
    return;
  case AI_ACTION_2_TRIBUTE_SUMMON:
  case AI_ACTION_PERM_CARD_2_TRIBUTE_SUMMON:
    SetPendingSummonTributeCount(2);
    return;
  case AI_ACTION_3_TRIBUTE_SUMMON:
  case AI_ACTION_PERM_CARD_3_TRIBUTE_SUMMON:
    SetPendingSummonTributeCount(3);
    return;
  default:
    return;
  }
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
  RecordAiSummonTributeCount();
  TryCaptureGreatMajuGarzettAiTribute();
  sub_803FD14();
  g8DFF600[sAI_Command.action]();
  AiMemory_RecordExecutedAction();
}
