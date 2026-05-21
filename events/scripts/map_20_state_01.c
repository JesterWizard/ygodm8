#include "event_macros.h"
#include "overworld.h"

/* map_20_state_01: map 20 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E84F30, map_20_state_01_08E84F30, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "A big guy took off running\nup the stairs.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F3C, map_20_state_01_08E84F3C, 0x08F04040, 0x08F04040)
  LANGUAGE_TEXT(0, "This is where I lost. I have\nno more ante cards.\n\n")
  END_LANGUAGE_TEXT()
  FALLTHROUGH()
END_EVENT_SCRIPT()
