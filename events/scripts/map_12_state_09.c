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

EVENT_SCRIPT_REPLACEMENT(0x08E6F120, map_12_state_09_08E6F120, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "My big brother turned\n"
      "Tristan into a monkey?\n\n"
      "That is the nuttiest thing I\n"
      "ever heard!\n\n"
      "Why would Seto do that!\n\n"
      "...But that reminds me...\n\n"
      "We made monkey robots, but\n"
      "they never sold well.\n\n"
      "I think we donated them to\n"
      "some island.\n\n"
  )
  SET_FLAG(EVENT_FLAG_ASKED_MOKUBA_ABOUT_THE_MONKEY_ROBOTS)
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E6F12C, map_12_state_09_08E6F12C, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT
  (
      "We programmed the monkey\n"
      "robots to behave like real\n\n"
      "monkeys.\n\n"
      "So if you show one a banana,\n"
      "it becomes excited.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
