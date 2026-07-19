#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_15_state_05: map 15 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E7A614, map_15_state_05_08E7A614, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_KAIBAS_BUTLER)
  LOAD_SPRITE(2, SPRITE_DOMINO_STATION_GUARD_2)
  TEXT(
      "Take this train if you want to go to the Egypt",
      "Exhibition."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A620, map_15_state_05_08E7A620, EVENT_NOP, EVENT_NOP)
  TEXT(
      "This train will be departing shortly.",
      "Please wait on board."
  )
  FALLTHROUGH()
END_EVENT_SCRIPT()
