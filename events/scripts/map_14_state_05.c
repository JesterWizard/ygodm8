#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_14_state_05: map 14 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E7748C, map_14_state_05_08E7748C, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_NON_DUELIST_PASSENGER)
  LOAD_SPRITE(2, SPRITE_DOMINO_STATION_GUARD)
  TEXT("Those Neo Ghoul weirdoes are finally gone.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77498, map_14_state_05_08E77498, EVENT_NOP, EVENT_NOP)
  TEXT("Sorry, I don't have time for fun and games.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E774BC, map_14_state_05_08E774BC, EVENT_NOP, EVENT_NOP)
  TEXT(
      "The Neo Ghouls at the turnstiles may have left...",
      "But unfortunately, there are still more on the train.",
      "If you board the train, please be careful."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
