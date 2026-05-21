#include "event_macros.h"
#include "overworld.h"

/* map_00_state_15: map 0 state 15 */

EVENT_SCRIPT_REPLACEMENT(0x08E34DF0, map_00_state_15_08E34DF0, 0x08F04040, 0x08F04040)
  PORTRAIT(PORTRAIT_ISHIZU, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("We must make our way to\nPegasus's island.\n\nWe must thwart Reshef the\nDark Being.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
