#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
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

u8 IsAiTributeSummonAction(u16 action)
{
  switch (action) {
    case AI_ACTION_1_TRIBUTE_SUMMON:
    case AI_ACTION_2_TRIBUTE_SUMMON:
    case AI_ACTION_3_TRIBUTE_SUMMON:
    case AI_ACTION_PERM_CARD_1_TRIBUTE_SUMMON:
    case AI_ACTION_PERM_CARD_2_TRIBUTE_SUMMON:
    case AI_ACTION_PERM_CARD_3_TRIBUTE_SUMMON:
      return TRUE;
    default:
      return FALSE;
  }
}

static u8 TryBlockAiTributeSummonAction(void)
{
  if (!IsAiTributeSummonAction(sAI_Command.action))
    return FALSE;

  if (!TryBlockTributeWithMaskOfRestrict())
    return FALSE;

  PlayMusic(SFX_TRAP_TRIGGERED);
  UpdateDuelGfxExceptField();
  return TRUE;
}

LYN_REPLACE_CHECK(sub_800E0D4);
void sub_800E0D4__Replacement(void)
{
  if (TryBlockAiTributeSummonAction())
    return;

  sub_803FD14();
  g8DFF600[sAI_Command.action]();
}
