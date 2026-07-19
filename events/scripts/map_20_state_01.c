#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_20_state_01: map 20 state 1 */

EVENT_SCRIPT_REPLACEMENT(0x08E84F30, map_20_state_01_08E84F30, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_YELLOW_SHIRT)
  TEXT("A big guy took off running up the stairs.")
  FALLTHROUGH()
END_EVENT_SCRIPT()

EVENT_SCRIPT_REPLACEMENT(0x08E84F3C, map_20_state_01_08E84F3C, EVENT_NOP, EVENT_NOP)
  TEXT("This is where I lost. I have no more ante cards.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
