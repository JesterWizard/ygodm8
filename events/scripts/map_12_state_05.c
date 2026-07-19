#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_05: map 12 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F00C, map_12_state_05_08E6F00C, EVENT_NOP, EVENT_NOP)
  LOAD_SPRITE(1, SPRITE_ROLAND)
  LOAD_SPRITE(2, SPRITE_MOKUBA)
  TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO, "Tristan and Duke are training inside.")
  FALLTHROUGH()
END_EVENT_SCRIPT()
