#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_14_state_06: map 14 state 6 */

EVENT_SCRIPT_REPLACEMENT(0x08E774C8, map_14_state_06_08E774C8, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_NON_DUELIST_PASSENGER)
  LOAD_SPRITE(2, SPRITE_DOMINO_STATION_GUARD)
  TEXT("The next stop is the Egypt Exhibition.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E774D4, map_14_state_06_08E774D4, EVENT_NOP, EVENT_NOP)
  TEXT("Sorry, I'm working.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
