#include "event_macros.h"
#include "overworld.h"

/* map_12_state_10: map 12 state 10 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F0F0, map_12_state_10_08E6F0F0, 0x08E6F0FC, 0x08E6F108)
  CHECK_FLAG(EVENT_FLAG_TOLD_ROLAND_MOKUBA_WAS_KIDNAPPED)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F0FC, map_12_state_10_08E6F0FC, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("Master Mokuba was abducted?\n\nThe last thing I know was\nthat he left to tell Master\n\nSeto...\n\nThat the Neo Ghouls had been\ndriven out of the Town of\n\nDomino...\n\nI've failed as a security\nguard...\n\nYou must save Master Mokuba.\n\nPlease help Master Seto\nrescue him.\n\n")
  SET_FLAG(EVENT_FLAG_TOLD_ROLAND_MOKUBA_WAS_KIDNAPPED)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F108, map_12_state_10_08E6F108, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("You must save Master Mokuba.\n\nPlease help Master Seto\nrescue him.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
