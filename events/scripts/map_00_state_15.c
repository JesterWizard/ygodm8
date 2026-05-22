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
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("We must make our way to\nPegasus's island.\n\nWe must thwart Reshef the\nDark Being.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
