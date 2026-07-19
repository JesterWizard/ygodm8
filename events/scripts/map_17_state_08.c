#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_17_state_08: map 17 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08E7F1A8, map_17_state_08_08E7F1A8, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_NON_DUELIST_PASSENGER)
  TEXT(
      "The train is the best way to travel. How else can you",
      "see the beautiful scenery?",
      "It's too bad I'm getting off after only one stop."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7F1B4, map_17_state_08_08E7F1B4, EVENT_NOP, EVENT_NOP)
  TEXT(
      "I'm taking a vacation by train.",
      "Please let me enjoy this time alone."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
