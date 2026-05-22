#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_14_state_03: map 14 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E77414, map_14_state_03_08E77414, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_DOMINO_STATION_GUARD)
  LOAD_SPRITE(2, SPRITE_DOMINO_STATION_GUARD)
  LOAD_SPRITE(3, SPRITE_DOMINO_STATION_GUARD)
  LOAD_SPRITE(4, SPRITE_NON_DUELIST_PASSENGER)
  TEXT
  (
      "First class costs too much.\n"
      "An economy seat will do.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77420, map_14_state_03_08E77420, 0x08F04040, 0x08F04040)
  TEXT
  (
      "This is where they punch\n"
      "your ticket.\n\n"
      "Go shuffle your deck\n"
      "somewhere else.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
