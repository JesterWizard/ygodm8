#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_14_state_05: map 14 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E7748C, map_14_state_05_08E7748C, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_NON_DUELIST_PASSENGER)
  LOAD_SPRITE(2, SPRITE_DOMINO_STATION_GUARD)
  TEXT
  (
      "Those Neo Ghoul weirdoes\n"
      "are finally gone.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E77498, map_14_state_05_08E77498, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Sorry, I don't have time for\n"
      "fun and games.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E774BC, map_14_state_05_08E774BC, 0x08F04040, 0x08F04040)
  TEXT
  (
      "The Neo Ghouls at the\n"
      "turnstiles may have left...\n\n"
      "But unfortunately, there are\n"
      "still more on the train.\n\n"
      "If you board the train,\n"
      "please be careful.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
