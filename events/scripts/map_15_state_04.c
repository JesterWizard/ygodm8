#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_15_state_04: map 15 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E7A5F0, map_15_state_04_08E7A5F0, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_KAIBAS_BUTLER)
  LOAD_SPRITE(2, SPRITE_DOMINO_STATION_GUARD_2)
  TEXT
  (
      "The Neo Ghouls robbed me of\n"
      "all my rare cards.\n\n"
      "I can't duel anymore.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5FC, map_15_state_04_08E7A5FC, 0x08F04040, 0x08F04040)
  TEXT
  (
      "The next stop is the Egypt\n"
      "Exhibition...\n\n"
      "But the Neo Ghouls have\n"
      "taken over the train.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A608, map_15_state_04_08E7A608, 0x08F04040, 0x08F04040)
  TEXT
  (
      "Please don't joke at a time\n"
      "like this.\n\n"
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
