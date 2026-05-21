#include "event_macros.h"
#include "overworld.h"

/* map_15_state_05: map 15 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E7A614, map_15_state_05_08E7A614, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_KAIBAS_BUTLER)
  LOAD_SPRITE(2, SPRITE_DOMINO_STATION_GUARD_2)
  TEXT("Take this train if you want\nto go to the Egypt\n\nExhibition.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E7A620, map_15_state_05_08E7A620, 0x08F04040, 0x08F04040)
  TEXT("This train will be departing\nshortly.\n\nPlease wait on board.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
