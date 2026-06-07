#include "global.h"
#include "common-chax.h"
#include "ai_decision.h"
#include "debug_ruleset.h"
#include "the_unhappy_maiden.h"

u16 sub_800EF0C(void);

LYN_REPLACE_CHECK(sub_800EF0C);
u16 sub_800EF0C__Replacement(void) {
  u16 action;

  if (gForceActiveTurnEnd) {
    gForceActiveTurnEnd = FALSE;
    return 0;
  }

  action = AiDecision_PickAction();
  if (action == 0)
    DebugRuleset_TryEnforceMustPlayMonsterRule();

  return action;
}
