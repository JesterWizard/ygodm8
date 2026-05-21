#include "event_macros.h"
#include "overworld.h"

/* map_25_state_01: map 25 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E99588, map_25_state_01_08E99588, 0x08F04040, 0x08F04040)
  TEXT("Welcome! I hope you enjoy\nyourselves!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E99594, map_25_state_01_08E99594, 0x08F04040, 0x08F04040)
  TEXT("We have a duel specialist on\nboard.\n\nThe specialist is on the\nfloor in the next section.\n\nPlease challenge her.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995A0, map_25_state_01_08E995A0, 0x08F04040, 0x08F04040)
  TEXT("That dealer... I think he's\ncheating.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E995AC, map_25_state_01_08E995AC, 0x08F04040, 0x08F04040)
  TEXT("A duel? What's that? Can I\nwin money?\n\nThere's no money involved?\nThen what's the point?\n\nHow can you be into a game\nwhen there's no cash at\n\nstake?\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
