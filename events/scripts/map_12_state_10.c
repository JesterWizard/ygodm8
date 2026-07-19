#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_10: map 12 state 10 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F0F0, map_12_state_10_08E6F0F0, 0x08E6F0FC, 0x08E6F108)
  LOAD_SPRITE(1, SPRITE_ROLAND)
  CHECK_FLAG(EVENT_FLAG_TOLD_ROLAND_MOKUBA_WAS_KIDNAPPED)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F0FC, map_12_state_10_08E6F0FC, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "Master Mokuba was abducted?",
      "The last thing I know was that he left to tell Master",
      "Seto...",
      "That the Neo Ghouls had been driven out of the Town of",
      "Domino...",
      "I've failed as a security guard...",
      "You must save Master Mokuba.",
      "Please help Master Seto rescue him."
  )
  SET_FLAG(EVENT_FLAG_TOLD_ROLAND_MOKUBA_WAS_KIDNAPPED)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F108, map_12_state_10_08E6F108, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_ROLAND, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "You must save Master Mokuba.",
      "Please help Master Seto rescue him."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
