#include "global.h"
#include "common-chax.h"
#include "ai_decision.h"
#include "the_unhappy_maiden.h"

u16 sub_800EF0C(void);

LYN_REPLACE_CHECK(sub_800EF0C);
u16 sub_800EF0C__Replacement(void) {
  if (gForceActiveTurnEnd) {
    gForceActiveTurnEnd = FALSE;
    return 0;
  }
  return AiDecision_PickAction();
}
