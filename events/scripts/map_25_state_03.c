#include "event_macros.h"
#include "overworld.h"

/* map_25_state_03: map 25 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E99600, map_25_state_03_08E99600, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "I bet you're duelists.\n\nNo, I'm not psychic. It's\nobvious because you're\n\nwearing Duel Disks.\n\nUnfortunately, I don't duel.\n\nYou should go to the next\nfloor.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E9960C, map_25_state_03_08E9960C, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "I hear that dealer dislikes\nduelists.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E99618, map_25_state_03_08E99618, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "No thanks. I don't duel.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
