#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_00_state_15: map 0 state 15 */

EVENT_SCRIPT_REPLACEMENT(0x08E34DF0, map_00_state_15_08E34DF0, 0x08F04040, 0x08F04040)
  LOAD_SPRITE(1, SPRITE_ISHIZU)
  LOAD_SPRITE(2, SPRITE_ESPA)
  LOAD_SPRITE(3, SPRITE_ROBA_BROTHER_1)
  LOAD_SPRITE(4, SPRITE_ROBA_BROTHER_2)
  LOAD_SPRITE(5, SPRITE_ROBA_BROTHER_3)
  TALK(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO,
    "We must make our way to\n"
    "Pegasus's island.\n\n"
    "We must thwart Reshef the\n"
    "Dark Being.\n\n"
)
  FALLTHROUGH()
END_EVENT_SCRIPT()
