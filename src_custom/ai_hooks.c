#include "global.h"
#include "common-chax.h"
#include "ai_decision.h"
#include "call_of_the_haunted.h"
#include "debug_ruleset.h"
#include "duel.h"
#include "permanent_effect.h"
#include "the_unhappy_maiden.h"

struct AI_Command {
  u16 action;
  u8 zone1Position;
  u8 zone2Position;
  u8 zone3Position;
  u8 zone4Position;
  u8 zone5Position;
  u8 zone6Position;
};

extern const struct AI_Command gAED58[];
extern struct AI_Command sAI_Command;

void sub_800EE24__Replacement(void);
void sub_800EE94__Replacement(void);
u16 sub_800EF0C(void);

typedef void (*FnVoid)(void);
typedef u8 (*FnU8Void)(void);

static inline void CallThumbVoid(u32 addr)
{
  ((FnVoid)(addr | 1))();
}

static inline u8 CallThumbU8(u32 addr)
{
  return ((FnU8Void)(addr | 1))();
}

static void AiClearCommandData(void)
{
  g2021BF8 = 0;
  sAI_Command.action = 0;
  sAI_Command.zone1Position = 0;
  sAI_Command.zone2Position = 0;
  sAI_Command.zone3Position = 0;
  sAI_Command.zone4Position = 0;
  sAI_Command.zone5Position = 0;
  sAI_Command.zone6Position = 0;
}

static void AiInitCommandData(u16 arg0)
{
  g2021BF8 = arg0;
  sAI_Command.action = gAED58[arg0].action;
  sAI_Command.zone1Position = gAED58[arg0].zone1Position;
  sAI_Command.zone2Position = gAED58[arg0].zone2Position;
  sAI_Command.zone3Position = gAED58[arg0].zone3Position;
  sAI_Command.zone4Position = gAED58[arg0].zone4Position;
  sAI_Command.zone5Position = gAED58[arg0].zone5Position;
  sAI_Command.zone6Position = gAED58[arg0].zone6Position;
}

void AiResimulateAllActions(void)
{
  u16 i;

  AiClearCommandData();
  CallThumbVoid(0x0800F108);
  for (i = 0, gHideEffectText = 1; i < 0x3B2; i++) {
    AiInitCommandData(i);
    if (CallThumbU8(0x0801A08C) == 1) {
      sub_800EE24__Replacement();
      CallThumbVoid(0x0800F1EC);
      CallThumbVoid(0x0800E0F8);
      TryActivatingPermanentEffects();
      CallThumbVoid(0x0800F248);
      sub_800EE94__Replacement();
    }
  }
  gHideEffectText = 0;
}

LYN_REPLACE_CHECK(sub_800EF0C);
u16 sub_800EF0C__Replacement(void) {
  u16 action;

  if (gForceActiveTurnEnd) {
    gForceActiveTurnEnd = FALSE;
    return 0;
  }

  if (gAiResimulateAfterCallOfTheHaunted) {
    CallOfTheHauntedUnlockAiAttackerAfterTrap();
    AiResimulateAllActions();
    gAiResimulateAfterCallOfTheHaunted = FALSE;
  }

  action = AiDecision_PickAction();
  if (action == 0)
    DebugRuleset_TryEnforceMustPlayMonsterRule();

  return action;
}
