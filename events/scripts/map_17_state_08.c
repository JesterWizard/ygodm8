#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_17_state_08: map 17 state 8 */

EVENT_SCRIPT_REPLACEMENT(0x08E7F1A8, map_17_state_08_08E7F1A8, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_NON_DUELIST_PASSENGER)
  TEXT
  (
      "The train is the best way to\n"
      "travel. How else can you\n\n"
      "see the beautiful scenery?\n\n"
      "It's too bad I'm getting off\n"
      "after only one stop.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7F1B4, map_17_state_08_08E7F1B4, 0x08F04040, 0x08F04040)
  TEXT
  (
      "I'm taking a vacation by\n"
      "train.\n\n"
      "Please let me enjoy this\n"
      "time alone.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
