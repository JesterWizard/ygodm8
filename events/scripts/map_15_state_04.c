#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_15_state_04: map 15 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08E7A5F0, map_15_state_04_08E7A5F0, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_KAIBAS_BUTLER)
  LOAD_SPRITE(2, SPRITE_DOMINO_STATION_GUARD_2)
  TEXT(
      "The Neo Ghouls robbed me of all my rare cards.",
      "I can't duel anymore."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A5FC, map_15_state_04_08E7A5FC, EVENT_NOP, EVENT_NOP)
  TEXT(
      "The next stop is the Egypt Exhibition...",
      "But the Neo Ghouls have taken over the train."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A608, map_15_state_04_08E7A608, EVENT_NOP, EVENT_NOP)
  TEXT("Please don't joke at a time like this.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
