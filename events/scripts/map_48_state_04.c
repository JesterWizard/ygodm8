#include "event_macros.h"
#include "overworld.h"

/* map_48_state_04: map 48 state 4 */

EVENT_SCRIPT_REPLACEMENT(0x08EDE8E4, map_48_state_04_08EDE8E4, 0x08EDE8F0, 0x08F04040)
  PLAY_MUSIC(17)
  PORTRAIT(PORTRAIT_YUGI, EXPRESSION_NEUTRAL, PORTRAIT_POSITION_AUTO)
  TEXT("I also have to get the\nspirit of the Puzzle back.\n\nThat's why I have to keep up\nwith your skills, {PLAYER}.\n\n")
  FALLTHROUGH()
END_EVENT_SCRIPT()
