#include "event_macros.h"
#include "overworld.h"

/* map_48_state_05: map 48 state 5 */

EVENT_SCRIPT_REPLACEMENT(0x08EDE980, map_48_state_05_08EDE980, 0x08EDE98C, 0x08F04040)
  PLAY_MUSIC(400)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("That's why I can't waste any\ntime.\n\nI won't be stopped!\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
