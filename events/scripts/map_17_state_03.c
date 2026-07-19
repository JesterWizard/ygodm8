#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_17_state_03: map 17 state 3 */

EVENT_SCRIPT_REPLACEMENT(0x08E7F148, map_17_state_03_08E7F148, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_NON_DUELIST_PASSENGER)
  TEXT("I should've taken first class...")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7F154, map_17_state_03_08E7F154, EVENT_NOP, EVENT_NOP)
  TEXT(
      "This is the train's deck!",
      "Don't confuse it with a duel deck!"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
