#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_09: map 12 state 9 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F114, map_12_state_09_08E6F114, 0x08E6F120, 0x08E6F12C)
  LOAD_SPRITE(1, SPRITE_ROLAND)
  LOAD_SPRITE(2, SPRITE_MOKUBA)
  CHECK_FLAG(EVENT_FLAG_ASKED_MOKUBA_ABOUT_THE_MONKEY_ROBOTS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F120, map_12_state_09_08E6F120, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "My big brother turned Tristan into a monkey?",
      "That is the nuttiest thing I ever heard!",
      "Why would Seto do that!",
      "...But that reminds me...",
      "We made monkey robots, but they never sold well.",
      "I think we donated them to some island."
  )
  SET_FLAG(EVENT_FLAG_ASKED_MOKUBA_ABOUT_THE_MONKEY_ROBOTS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F12C, map_12_state_09_08E6F12C, EVENT_NOP, EVENT_NOP)
  TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
      "We programmed the monkey robots to behave like real",
      "monkeys.",
      "So if you show one a banana, it becomes excited."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
