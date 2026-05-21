#include "event_macros.h"
#include "overworld.h"

/* map_14_state_03: map 14 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E77414, map_14_state_03_08E77414, 0x08F04040, 0x08F04040)
  TEXT("First class costs too much.\nAn economy seat will do.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77420, map_14_state_03_08E77420, 0x08F04040, 0x08F04040)
  TEXT("This is where they punch\nyour ticket.\n\nGo shuffle your deck\nsomewhere else.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
