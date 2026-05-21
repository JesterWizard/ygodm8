#include "event_macros.h"
#include "overworld.h"

/* map_55_state_02: map 55 state 2 */

EVENT_SCRIPT_REPLACEMENT(0x08EF0570, map_55_state_02_08EF0570, 0x08F04040, 0x08F04040)
  DELAY(128)
  FADE_SCREEN(8)
  WARP(54, 3, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
