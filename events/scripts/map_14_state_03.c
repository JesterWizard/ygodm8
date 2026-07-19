#include "event_macros.h"
#include "event_object_slots.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_14_state_03: map 14 state 3 */

#define LOCALID_STATION_GUARD_1  1
#define LOCALID_STATION_GUARD_2  2
#define LOCALID_STATION_GUARD_3  3

EVENT_SCRIPT_REPLACEMENT(0x08E77414, map_14_state_03_08E77414, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(LOCALID_STATION_GUARD_1, SPRITE_DOMINO_STATION_GUARD)
  LOAD_SPRITE(LOCALID_STATION_GUARD_2, SPRITE_DOMINO_STATION_GUARD)
  LOAD_SPRITE(LOCALID_STATION_GUARD_3, SPRITE_DOMINO_STATION_GUARD)
  LOAD_SPRITE(4, SPRITE_NON_DUELIST_PASSENGER)
  TEXT("First class costs too much. An economy seat will do.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77420, map_14_state_03_08E77420, EVENT_NOP, EVENT_NOP)
  TEXT(
      "This is where they punch your ticket.",
      "Go shuffle your deck somewhere else."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
