#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_10: map 12 state 10 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F0F0, map_12_state_10_08E6F0F0, 0x08E6F0FC, 0x08E6F108)
  LOAD_SPRITE(1, SPRITE_ROLAND)
  CHECK_FLAG(EVENT_FLAG_TOLD_ROLAND_MOKUBA_WAS_KIDNAPPED)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F0FC, map_12_state_10_08E6F0FC, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Master Mokuba was abducted?\n\n"
    "The last thing I know was\n"
    "that he left to tell Master\n\n"
    "Seto...\n\n"
    "That the Neo Ghouls had been\n"
    "driven out of the Town of\n\n"
    "Domino...\n\n"
    "I've failed as a security\n"
    "guard...\n\n"
    "You must save Master Mokuba.\n\n"
    "Please help Master Seto\n"
    "rescue him.\n\n"
)
  SET_FLAG(EVENT_FLAG_TOLD_ROLAND_MOKUBA_WAS_KIDNAPPED)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F108, map_12_state_10_08E6F108, 0x08F04040, 0x08F04040)
  TALK(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "You must save Master Mokuba.\n\n"
    "Please help Master Seto\n"
    "rescue him.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
