#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_12_state_05: map 12 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08E6F00C, map_12_state_05_08E6F00C, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_ROLAND)
  LOAD_SPRITE(2, SPRITE_MOKUBA)
  TALK(PORTRAIT_MOKUBA, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "Tristan and Duke are\n"
    "training inside.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
