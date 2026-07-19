#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_33_state_00: map 33 state 0 */

EVENT_SCRIPT_REPLACEMENT(0x08EBEC58, map_33_state_00_08EBEC58, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_PARADOX)
  WARP(LOCATION_PEGASUS_CASTLE_RIGHT_ROOM, 2, 0, 0)
  FALLTHROUGH()
END_EVENT_SCRIPT()
